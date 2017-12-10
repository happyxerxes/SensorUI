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
//ui
    ui->wifiOpenButton->setEnabled(false); ui->wifiOpenButton->setText("正常连接");
    ui->flaglabel_dbstatus->setStyleSheet("border-radius:10px;background-color:green;");

    ui->flaglabel_1->clear();
    ui->flaglabel_1->setStyleSheet("border-radius:8px;background-color:red;");

    ui->flaglabel_2->clear();
    ui->flaglabel_2->setStyleSheet("border-radius:8px;background-color:red;");

    ui->label_25->setVisible(false);
    ui->labelTime->setVisible(false);
    ui->lineEdit_id_1->setText("Ba1");
    ui->lineEdit_id_2->setText("Ba2");
    ui->lineEdit_id_1->setEnabled(false);
    ui->lineEdit_id_2->setEnabled(false);
    ui->lineEdit_id_1->setVisible(false);
    ui->lineEdit_id_2->setVisible(false);
    ui->label_16->setVisible(false);
    ui->label_2->setVisible(false);


    ui->textEdit_2->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->nameLine->setVisible(false);
    ui->textEdit_2->setFont(QFont("Timers" , 24 ,  QFont::Bold));
    ui->textEdit->setFont(QFont("Timers" , 20 ,  QFont::Bold));
    ui->labelTime->setFont(QFont("Timers" , 12 ,  QFont::Bold));
    ui->labelTime_2->setFont(QFont("Timers" , 12 ,  QFont::Bold));

    ui->nameLine->setFont(QFont("Timers" , 30 ,  QFont::Bold));
    ui->lineEdit_id_1->setFont(QFont("Timers" , 20 ,  QFont::Bold));
    ui->lineEdit_id_2->setFont(QFont("Timers" , 20 ,  QFont::Bold));




    ui->lineEdit_wendu->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_shidu->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_co2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_guangzhaodu->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_daqiyali->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_wendu_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_shidu_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_co2_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_guangzhaodu_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_daqiyali_2->setFocusPolicy(Qt::NoFocus);

    ui->lineEdit_wendu->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_shidu->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_co2->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_guangzhaodu->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_daqiyali->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_wendu_2->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_shidu_2->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_co2_2->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_guangzhaodu_2->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_daqiyali_2->setFont(QFont("Timers" , 28 ,  QFont::Bold));

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
void MainWindow::chulidata(char* buf)
{
    if(lockflag == true){return;}
    float wendu = QVariant(((unsigned char)buf[3]*256+(unsigned char)buf[4])).toFloat()/100;
    if (wendu>327){ //温度小于0
        wendu = wendu-655.36;
    }
    QString wenduS = QString::number(wendu, 'f', 2);
    ui->lineEdit_wendu->clear();
    ui->lineEdit_wendu->insert(wenduS);

    float shidu = QVariant(((unsigned char)buf[5]*256+(unsigned char)buf[6])).toFloat()/100;
    QString shiduS = QString::number(shidu, 'f', 2);
    ui->lineEdit_shidu->clear();
    ui->lineEdit_shidu->insert(shiduS);

    float guangzhaodu = QVariant(((unsigned char)buf[7]*256+(unsigned char)buf[8])).toFloat();
    QString guangzhaoduS = QString::number(guangzhaodu, 'f', 0);
    ui->lineEdit_guangzhaodu->clear();
    ui->lineEdit_guangzhaodu->insert(guangzhaoduS);

    float co2 = QVariant(((unsigned char)buf[9]*256+(unsigned char)buf[10])).toFloat();
    QString co2S = QString::number(co2, 'f', 0);
    ui->lineEdit_co2->clear();
    ui->lineEdit_co2->insert(co2S);

    float daqiyali = QVariant(((unsigned char)buf[11]*256+(unsigned char)buf[12])).toFloat()/100;
    QString daqiyaliS = QString::number(daqiyali, 'f', 2);
    ui->lineEdit_daqiyali->clear();
    ui->lineEdit_daqiyali->insert(daqiyaliS);




    time = QDateTime::currentDateTime();
    QString ttime = time.toString("yyyy-MM-dd hh:mm:ss");
    int tttime =time.toTime_t();
    QString tyear = time.toString("yyyy");
    QString tmonth = time.toString("MM");
    QString tday = time.toString("dd");
    QString thour = time.toString("hh");

    //qDebug() << QString::number(ttime);
    //qDebug() << QString::number(ttime-ttime_pre);

    if( tttime-ttime_pre_1 > 300){


            ttime_pre_1 = tttime;

            //send co2 to database
            QSqlQuery sql_query;
            //QString update_sql = "INSERT INTO test  VALUES (:id,:wd,:sd,:gzd,:co2,:dqyl,NULL) ON DUPLICATE KEY UPDATE wd=:wd,sd=:sd,gzd=:gzd,co2=:co2,dqyl=:dqyl";
            QString update_sql = "INSERT INTO stat (id,wd,sd,gzd,co2,dqyl,fs,ttime,tyear,tmonth,tday,thour) VALUES (:id,:wd,:sd,:gzd,:co2,:dqyl,NULL,:ttime,:tyear,:tmonth,:tday,:thour)";


            sql_query.prepare(update_sql);
            sql_query.bindValue(":id", ui->lineEdit_id_1->text());
            sql_query.bindValue(":wd", wendu);
            sql_query.bindValue(":sd", shidu);
            sql_query.bindValue(":gzd", guangzhaodu);
            sql_query.bindValue(":co2", co2);
            sql_query.bindValue(":dqyl", daqiyali);
            sql_query.bindValue(":ttime", ttime);
            sql_query.bindValue(":tyear", tyear);
            sql_query.bindValue(":tmonth", tmonth);
            sql_query.bindValue(":tday", tday);
            sql_query.bindValue(":thour", thour);

            sql_query.exec();
    }


    //send co2 to database
    QSqlQuery sql_query;
    QString update_sql = "INSERT INTO test  VALUES (:id,:wd,:sd,:gzd,:co2,:dqyl,NULL,:ttime) ON DUPLICATE KEY UPDATE wd=:wd,sd=:sd,gzd=:gzd,co2=:co2,dqyl=:dqyl,ttime=:ttime";
    //QString update_sql = "INSERT INTO test (id,wd,sd,gzd,co2,dqyl,fs,ttime) VALUES (:id,:wd,:sd,:gzd,:co2,:dqyl,NULL,:ttime)";



    sql_query.prepare(update_sql);
    sql_query.bindValue(":id", ui->lineEdit_id_1->text());
    sql_query.bindValue(":wd", wendu);
    sql_query.bindValue(":sd", shidu);
    sql_query.bindValue(":gzd", guangzhaodu);
    sql_query.bindValue(":co2", co2);
    sql_query.bindValue(":dqyl", daqiyali);
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

        ui->wifiOpenButton->setEnabled(false); ui->wifiOpenButton->setText(tr("重新连接"));
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
    float wendu = QVariant(((unsigned char)buf[3]*256+(unsigned char)buf[4])).toFloat()/100;
    if (wendu>327){ //温度小于0
        wendu = wendu-655.36;
    }
    QString wenduS = QString::number(wendu, 'f', 2);
    ui->lineEdit_wendu_2->clear();
    ui->lineEdit_wendu_2->insert(wenduS);

    float shidu = QVariant(((unsigned char)buf[5]*256+(unsigned char)buf[6])).toFloat()/100;
    QString shiduS = QString::number(shidu, 'f', 2);
    ui->lineEdit_shidu_2->clear();
    ui->lineEdit_shidu_2->insert(shiduS);

    float guangzhaodu = QVariant(((unsigned char)buf[7]*256+(unsigned char)buf[8])).toFloat();
    QString guangzhaoduS = QString::number(guangzhaodu, 'f', 0);
    ui->lineEdit_guangzhaodu_2->clear();
    ui->lineEdit_guangzhaodu_2->insert(guangzhaoduS);

    float co2 = QVariant(((unsigned char)buf[9]*256+(unsigned char)buf[10])).toFloat();
    QString co2S = QString::number(co2, 'f', 0);
    ui->lineEdit_co2_2->clear();
    ui->lineEdit_co2_2->insert(co2S);

    float daqiyali = QVariant(((unsigned char)buf[11]*256+(unsigned char)buf[12])).toFloat()/100;
    QString daqiyaliS = QString::number(daqiyali, 'f', 2);
    ui->lineEdit_daqiyali_2->clear();
    ui->lineEdit_daqiyali_2->insert(daqiyaliS);

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

            qDebug() <<"111" ;

            ttime_pre_2 = tttime;

            //send co2 to database
            QSqlQuery sql_query;
            //QString update_sql = "INSERT INTO test  VALUES (:id,:wd,:sd,:gzd,:co2,:dqyl,NULL) ON DUPLICATE KEY UPDATE wd=:wd,sd=:sd,gzd=:gzd,co2=:co2,dqyl=:dqyl";
            QString update_sql = "INSERT INTO stat (id,wd,sd,gzd,co2,dqyl,fs,ttime,tyear,tmonth,tday,thour) VALUES (:id,:wd,:sd,:gzd,:co2,:dqyl,NULL,:ttime,:tyear,:tmonth,:tday,:thour)";


            sql_query.prepare(update_sql);
            sql_query.bindValue(":id", ui->lineEdit_id_2->text());
            sql_query.bindValue(":wd", wendu);
            sql_query.bindValue(":sd", shidu);
            sql_query.bindValue(":gzd", guangzhaodu);
            sql_query.bindValue(":co2", co2);
            sql_query.bindValue(":dqyl", daqiyali);
            sql_query.bindValue(":ttime", ttime);
            sql_query.bindValue(":tyear", tyear);
            sql_query.bindValue(":tmonth", tmonth);
            sql_query.bindValue(":tday", tday);
            sql_query.bindValue(":thour", thour);

            sql_query.exec();
    }


    //send co2 to database
    QSqlQuery sql_query;
    QString update_sql = "INSERT INTO test  VALUES (:id,:wd,:sd,:gzd,:co2,:dqyl,NULL,:ttime) ON DUPLICATE KEY UPDATE wd=:wd,sd=:sd,gzd=:gzd,co2=:co2,dqyl=:dqyl,ttime=:ttime";
    //QString update_sql = "INSERT INTO test (id,wd,sd,gzd,co2,dqyl,fs,ttime) VALUES (:id,:wd,:sd,:gzd,:co2,:dqyl,NULL,:ttime)";



    sql_query.prepare(update_sql);
    sql_query.bindValue(":id", ui->lineEdit_id_2->text());
    sql_query.bindValue(":wd", wendu);
    sql_query.bindValue(":sd", shidu);
    sql_query.bindValue(":gzd", guangzhaodu);
    sql_query.bindValue(":co2", co2);
    sql_query.bindValue(":dqyl", daqiyali);
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

        ui->wifiOpenButton->setEnabled(false); ui->wifiOpenButton->setText(tr("重新连接"));
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






void MainWindow::on_openButton_clicked()
{
    ui->openButton->setEnabled(false);
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
        ui->lineEdit_wendu->clear();
        ui->lineEdit_shidu->clear();
        ui->lineEdit_co2->clear();
        ui->lineEdit_guangzhaodu->clear();
        ui->lineEdit_daqiyali->clear();
        //恢复PortBox使能
        //ui->lineEdit_id_1->setEnabled(true);
        ui->PortBox->setEnabled(true);
         ui->openButton->setText(tr("打开串口"));
         ui->flaglabel_1->setStyleSheet("border-radius:8px;background-color:red;");


    }
    ui->openButton->setEnabled(true);
}
void MainWindow::on_openButton_2_clicked()
{
    ui->openButton_2->setEnabled(false);
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
        ui->lineEdit_id_2->setEnabled(false);
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
        ui->lineEdit_wendu_2->clear();
        ui->lineEdit_shidu_2->clear();
        ui->lineEdit_co2_2->clear();
        ui->lineEdit_guangzhaodu_2->clear();
        ui->lineEdit_daqiyali_2->clear();
        //恢复PortBox使能
        // ui->lineEdit_id_2->setEnabled(true);
        ui->PortBox_2->setEnabled(true);
        ui->openButton_2->setText(tr("打开串口"));
        ui->flaglabel_2->setStyleSheet("border-radius:8px;background-color:red;");

    }
    ui->openButton_2->setEnabled(true);
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
