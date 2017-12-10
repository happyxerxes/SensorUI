#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <qdatetime.h>
#include <QMessageBox>
#include <QInputDialog>
//#include <QVariant>
//#include <QProcess>

#define ERRORCOUNT 5

int ttime_pre_1 = 0;
int ttime_pre_2 = 0;
int reconnect_time_pre = 0;
int reconnect_time;

QDateTime time;

void MainWindow::mysql_init(){
    //mysql init
        if (QSqlDatabase::contains("qt_sql_default_connection"))
        {
            database = QSqlDatabase::database("qt_sql_default_connection");
        }
        else
        {
            database = QSqlDatabase::addDatabase("QMYSQL");
            //qDebug() << "MYSQL driver valid" << database.isValid();
            database.setHostName("123.206.24.89");
            database.setUserName("test");
            database.setPassword(text);
            database.setDatabaseName("test");
            database.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=2");
        }

        //qDebug() <<"111";
        bool r=database.open();
        //qDebug() << QString::number(r);

        //qDebug() <<"222";
        //qDebug() << database.lastError().nativeErrorCode();

        bool ok;
        int i = database.lastError().nativeErrorCode().toInt(&ok,10);
        if(i == 1045){
            is_wrong_passwd = true;
        }
        else {};
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//password
    text = QInputDialog::getText(NULL, "提示",
                                            "请输入数据库密码:",
                                            QLineEdit::Password,    //输入的是密码，不显示明文
                                            //QLineEdit::Normal,          //输入框明文
                                            NULL
                                            );

    mysql_init();


//show time
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

//ui init
    ui->wifiOpenButton->setEnabled(false); ui->wifiOpenButton->setText("正常连接");
    ui->flaglabel_dbstatus->setStyleSheet("border-radius:10px;background-color:green;");

    ui->flaglabel_1->clear();
    ui->flaglabel_1->setStyleSheet("border-radius:8px;background-color:red;");
    ui->flaglabel_2->clear();
    ui->flaglabel_2->setStyleSheet("border-radius:8px;background-color:red;");

    ui->label_25->setVisible(false);
    ui->labelTime->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->textEdit_3->setVisible(false);
    ui->textEdit_2->setFont(QFont("Timers" , 24 ,  QFont::Bold));
    ui->textEdit->setFont(QFont("Timers" , 20 ,  QFont::Bold));
    ui->textEdit_3->setFont(QFont("Timers" , 20 ,  QFont::Bold));
    ui->labelTime->setFont(QFont("Timers" , 12 ,  QFont::Bold));
    //ui->labelTime_2->setFont(QFont("Timers" , 12 ,  QFont::Bold));


    ui->lineEdit_id_1->setFont(QFont("Timers" , 20 ,  QFont::Bold));

    ui->lineEdit_id_1->setText("A2");
    ui->lineEdit_id_1->setEnabled(false);
    ui->lineEdit_id_1->setVisible(false);
    ui->label_2->setVisible(false);


    ui->lineEdit_co2->setFocusPolicy(Qt::NoFocus);

    ui->lineEdit_fs->setFocusPolicy(Qt::NoFocus);


    ui->lineEdit_co2->setFont(QFont("Timers" , 28 ,  QFont::Bold));

    ui->lineEdit_fs->setFont(QFont("Timers" , 28 ,  QFont::Bold));

 //2 threads
    workerThread = new WorkerThread(this);
    connect(workerThread, SIGNAL(resultReady(char*)), this, SLOT(chulidata(char*)));
    workerThread->start();

    workerThread_2 = new WorkerThread_2(this);
    connect(workerThread_2, SIGNAL(resultReady(char*)), this, SLOT(chulidata_2(char*)));
    workerThread_2->start();

       // qDebug() << tr("界面设定成功！");

}

MainWindow::~MainWindow()
{
    delete ui;
}


//chuli数据
float co2_pre = -1;
void MainWindow::chulidata(char* buf)
{
    if(lockflag == true){return;}


    float co2 = QVariant(((unsigned char)buf[3]*256+(unsigned char)buf[4])).toFloat();
    if(co2_pre != -1 && (co2-co2_pre>1000 || co2_pre-co2>1000) ) {co2_pre=co2;return;}//滤波
    co2_pre=co2;

    QString co2S = QString::number(co2, 'f', 0);
    ui->lineEdit_co2->clear();
    ui->lineEdit_co2->insert(co2S);


    time = QDateTime::currentDateTime();
    QString ttime = time.toString("yyyy-MM-dd hh:mm:ss");
    int tttime =time.toTime_t();
    QString tyear = time.toString("yyyy");
    QString tmonth = time.toString("MM");
    QString tday = time.toString("dd");
    QString thour = time.toString("hh");

    if( tttime-ttime_pre_1 > 300){


            ttime_pre_1 = tttime;

            //send co2 to database
            QSqlQuery sql_query;
            //QString update_sql = "INSERT INTO test  VALUES (:id,NULL,NULL,NULL,:co2,NULL,NULL) ON DUPLICATE KEY UPDATE co2=:co2";
            QString update_sql = "INSERT INTO stat (id,wd,sd,gzd,co2,dqyl,fs,ttime,tyear,tmonth,tday,thour) VALUES (:id,NULL,NULL,NULL,:co2,NULL,NULL,:ttime,:tyear,:tmonth,:tday,:thour)";
            sql_query.prepare(update_sql);
            sql_query.bindValue(":id", ui->lineEdit_id_1->text());
            sql_query.bindValue(":co2", co2);
            sql_query.bindValue(":ttime", ttime);
            sql_query.bindValue(":tyear", tyear);
            sql_query.bindValue(":tmonth", tmonth);
            sql_query.bindValue(":tday", tday);
            sql_query.bindValue(":thour", thour);

            sql_query.exec();

     }


    //send co2 to database
    QSqlQuery sql_query;
    QString update_sql = "INSERT INTO test  VALUES (:id,NULL,NULL,NULL,:co2,NULL,NULL,:ttime) ON DUPLICATE KEY UPDATE co2=:co2,ttime=:ttime";
    //QString update_sql = "INSERT INTO stat (id,wd,sd,gzd,co2,dqyl,fs,ttime,tyear,tmonth,tday,thour) VALUES (:id,NULL,NULL,NULL,:co2,NULL,NULL,:ttime,:tyear,:tmonth,:tday,:thour)";
    sql_query.prepare(update_sql);
    sql_query.bindValue(":id", ui->lineEdit_id_1->text());
    sql_query.bindValue(":co2", co2);
    sql_query.bindValue(":ttime", ttime);

    if(sql_query.exec())
    {
        error_count=0;
    }
    else{
        if(wifi_cut_flag){
           error_count=0;

        }
        else{
           error_count++;
        }
    }

    if(error_count > ERRORCOUNT && wifi_cut_flag == false){
        wifi_cut_flag=true;
        error_count = 0;

        if(is_wrong_passwd){
            QMessageBox::information(this,"提示2","数据库密码错误，请重启软件后输入正确密码!");
        }
        else{
            //QMessageBox::information(this,"提示1","网络连接错误，请检查网络后重新连接数据库!");
        }

        ui->wifiOpenButton->setEnabled(false);
        ui->flaglabel_dbstatus->setStyleSheet("border-radius:10px;background-color:red;");


        database.close();
        //this->close();
    }

    time = QDateTime::currentDateTime();
    reconnect_time = time.toTime_t();

    if(wifi_cut_flag == true){
        if(reconnect_time-reconnect_time_pre > 30){
            reconnect_time_pre = reconnect_time;

            mysql_init();

            wifi_cut_flag = false;

            ui->wifiOpenButton->setEnabled(false); ui->wifiOpenButton->setText(tr("正常连接"));
            ui->flaglabel_dbstatus->setStyleSheet("border-radius:10px;background-color:green;");
        }
    }


}
void MainWindow::chulidata_2(char* buf)
{
    if(lockflag_2 == true){return;}

    float fs = (float)(buf[1]-0x30)*10+(float)(buf[2]-0x30)+(float)(buf[3]-0x30)/10+(float)(buf[4]-0x30)/100;
    fs=fs*2.64;
    QString fsS = QString::number(fs, 'f', 2);
    ui->lineEdit_fs->clear();
    ui->lineEdit_fs->insert(fsS);


    time = QDateTime::currentDateTime();
    QString ttime = time.toString("yyyy-MM-dd hh:mm:ss");
    int tttime =time.toTime_t();
    QString tyear = time.toString("yyyy");
    QString tmonth = time.toString("MM");
    QString tday = time.toString("dd");
    QString thour = time.toString("hh");

    //qDebug() << QString::number(ttime);
    //qDebug() << QString::number(ttime-ttime_pre);

    if( tttime-ttime_pre_2 > 300){

            ttime_pre_2 = tttime;
            QSqlQuery sql_query;
            //QString update_sql = "INSERT INTO test  VALUES (:id,NULL,NULL,NULL,NULL,NULL,:fs) ON DUPLICATE KEY UPDATE fs=:fs";
            QString update_sql = "INSERT INTO stat (id,wd,sd,gzd,co2,dqyl,fs,ttime,tyear,tmonth,tday,thour) VALUES (:id,NULL,NULL,NULL,NULL,NULL,:fs,:ttime,:tyear,:tmonth,:tday,:thour)";

            sql_query.prepare(update_sql);
            sql_query.bindValue(":id", ui->lineEdit_id_1->text());
            sql_query.bindValue(":fs", fs);
            sql_query.bindValue(":ttime", ttime);
            sql_query.bindValue(":tyear", tyear);
            sql_query.bindValue(":tmonth", tmonth);
            sql_query.bindValue(":tday", tday);
            sql_query.bindValue(":thour", thour);

            sql_query.exec();

     }


    //send fs to database
    QSqlQuery sql_query;
    QString update_sql = "INSERT INTO test  VALUES (:id,NULL,NULL,NULL,NULL,NULL,:fs,:ttime) ON DUPLICATE KEY UPDATE fs=:fs,ttime=:ttime";
    sql_query.prepare(update_sql);
    sql_query.bindValue(":id", ui->lineEdit_id_1->text());
    sql_query.bindValue(":fs", fs);
    sql_query.bindValue(":ttime", ttime);
    if(sql_query.exec())
    {
        error_count=0;
    }
    else{
        if(wifi_cut_flag){
           error_count=0;

        }
        else{
           error_count++;
        }
    }

    if(error_count > ERRORCOUNT && wifi_cut_flag == false){
        wifi_cut_flag=true;
        error_count = 0;

        if(is_wrong_passwd){
            QMessageBox::information(this,"提示2","数据库密码错误，请重启软件后输入正确密码!");
        }
        else{
            //QMessageBox::information(this,"提示1","网络连接错误，请检查网络后重新连接数据库!");
        }

        ui->wifiOpenButton->setEnabled(false);
        ui->flaglabel_dbstatus->setStyleSheet("border-radius:10px;background-color:red;");


        database.close();
        //this->close();
    }

    time = QDateTime::currentDateTime();
    reconnect_time = time.toTime_t();

    if(wifi_cut_flag == true){
        if(reconnect_time-reconnect_time_pre > 30){
            reconnect_time_pre = reconnect_time;


            mysql_init();

            wifi_cut_flag = false;

            ui->wifiOpenButton->setEnabled(false); ui->wifiOpenButton->setText(tr("正常连接"));
            ui->flaglabel_dbstatus->setStyleSheet("border-radius:10px;background-color:green;");
        }
    }
}





/*
//delay ms
void MainWindow::sleep(unsigned int msecs){
    QTime reachTime = QTime::currentTime().addMSecs(msecs);
    while(QTime::currentTime() < reachTime)
         QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
*/





void MainWindow::on_openButton_clicked()
{
    if(ui->openButton->text()==tr("打开串口"))
    {

        lockflag = false;
        workerThread->unlock(ui->PortBox->currentText());
        //关闭PortBox使能
        ui->lineEdit_id_1->setEnabled(false);
        ui->PortBox->setEnabled(false);
        ui->openButton->setText(tr("关闭串口"));
        ui->flaglabel_1->setStyleSheet("border-radius:8px;background-color:green;");

/*
        //open database
        if(!database.isOpen()){

            QProcess *cmd = new QProcess;
            QString strArg = "ping 123.206.24.89 -n 1 -w 100";  //windows下的格式 ms
            cmd->start(strArg);
            cmd->waitForReadyRead();
            cmd->waitForFinished();
            QString retStr = cmd->readAll();
            if (retStr.indexOf("TTL") != -1)
            {
                qDebug() <<"is online!\n";
                database.open();
            }
            else{qDebug() <<"is not online!\n"; }
            retStr.clear();

        }
*/

    }
    else
    {
        lockflag = true;
        workerThread->lock();

        ui->lineEdit_co2->clear();

        //恢复PortBox使能
        //if(lockflag && lockflag_2){ui->lineEdit_id_1->setEnabled(true);}
        ui->PortBox->setEnabled(true);
        ui->openButton->setText(tr("打开串口"));
        ui->flaglabel_1->setStyleSheet("border-radius:8px;background-color:red;");





    }
}
void MainWindow::on_openButton_2_clicked()
{
    if(ui->openButton_2->text()==tr("打开串口"))
    {
        lockflag_2 = false;
        workerThread_2->unlock(ui->PortBox_2->currentText());
        //关闭PortBox使能
        ui->PortBox_2->setEnabled(false);
        ui->openButton_2->setText(tr("关闭串口"));

        lockflag_2 = false;
        workerThread_2->unlock(ui->PortBox_2->currentText());
        //关闭PortBox使能
        ui->lineEdit_id_1->setEnabled(false);
        ui->PortBox_2->setEnabled(false);
        ui->openButton_2->setText(tr("关闭串口"));
        ui->flaglabel_2->setStyleSheet("border-radius:8px;background-color:green;");

/*
        //open database
        if(!database.isOpen()){

            QProcess *cmd = new QProcess;
            QString strArg = "ping 123.206.24.89 -n 1 -w 100";  //windows下的格式 ms
            cmd->start(strArg);
            cmd->waitForReadyRead();
            cmd->waitForFinished();
            QString retStr = cmd->readAll();
            if (retStr.indexOf("TTL") != -1)
            {
                qDebug() <<"is online!\n";
                database.open();
            }
            else{qDebug() <<"is not online!\n"; }
            retStr.clear();

        }
*/

    }
    else
    {
        lockflag_2 = true;
        workerThread_2->lock();
        ui->lineEdit_fs->clear();

        //恢复PortBox使能
        if(lockflag && lockflag_2){ui->lineEdit_id_1->setEnabled(true);}

        ui->PortBox_2->setEnabled(true);
        ui->openButton_2->setText(tr("打开串口"));
        ui->flaglabel_2->setStyleSheet("border-radius:8px;background-color:red;");



    }
}

void MainWindow::on_wifiOpenButton_clicked(){
     //qDebug() << "kick";
    mysql_init();

    wifi_cut_flag = false;
    //workerThread->reset_wifi_cut_flag();

    ui->wifiOpenButton->setEnabled(false); ui->wifiOpenButton->setText(tr("正常连接"));
    ui->flaglabel_dbstatus->setStyleSheet("border-radius:10px;background-color:green;");


}

void MainWindow::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy年MM月dd日dddd hh时mm分");
    //QString str_2 = time.toString("hh时mm分");
    ui->labelTime->setText(str);
    //ui->labelTime_2->setText(str_2);
}
