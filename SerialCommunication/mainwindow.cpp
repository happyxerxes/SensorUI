#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <qdatetime.h>
#include <QMessageBox>
#include <QInputDialog>
#include <QVariant>
#include <QProcess>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//password
    QString text = QInputDialog::getText(NULL, "提示",
                                            "请输入数据库密码:",
                                            QLineEdit::Password,    //输入的是密码，不显示明文
                                            //QLineEdit::Normal,          //输入框明文
                                            NULL
                                            );
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
    }

//show time
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);
//ui

    ui->flaglabel_1->clear();
    ui->flaglabel_1->setStyleSheet("background-color:red;");

    ui->flaglabel_2->clear();
    ui->flaglabel_2->setStyleSheet("background-color:red;");

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

    //send co2 to database
    QSqlQuery sql_query;
    QString update_sql = "INSERT INTO test  VALUES (:id,:wd,:sd,:gzd,:co2,:dqyl,NULL) ON DUPLICATE KEY UPDATE wd=:wd,sd=:sd,gzd=:gzd,co2=:co2,dqyl=:dqyl";
    sql_query.prepare(update_sql);
    sql_query.bindValue(":id", ui->lineEdit_id_1->text());
    sql_query.bindValue(":wd", wendu);
    sql_query.bindValue(":sd", shidu);
    sql_query.bindValue(":gzd", guangzhaodu);
    sql_query.bindValue(":co2", co2);
    sql_query.bindValue(":dqyl", daqiyali);
    if(sql_query.exec())
    {
        error_count=0;
    }
    else{error_count++;}

    if(error_count > 10 && wifi_cut_flag == 1){
        wifi_cut_flag=0;
        if(database.isOpen()) database.close();
        QMessageBox::information(this,"提示","网络断开，请重新打开软件!");
        //this->close();
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

    //send co2 to database
    QSqlQuery sql_query;
    QString update_sql = "INSERT INTO test  VALUES (:id,:wd,:sd,:gzd,:co2,:dqyl,NULL) ON DUPLICATE KEY UPDATE wd=:wd,sd=:sd,gzd=:gzd,co2=:co2,dqyl=:dqyl";
    sql_query.prepare(update_sql);
    sql_query.bindValue(":id", ui->lineEdit_id_2->text());
    sql_query.bindValue(":wd", wendu);
    sql_query.bindValue(":sd", shidu);
    sql_query.bindValue(":gzd", guangzhaodu);
    sql_query.bindValue(":co2", co2);
    sql_query.bindValue(":dqyl", daqiyali);
    if(sql_query.exec())
    {
        error_count=0;
    }
    else{error_count++;}

    if(error_count > 10 && wifi_cut_flag == 1){
        wifi_cut_flag=0;
        if(database.isOpen()) database.close();
        QMessageBox::information(this,"提示","网络断开，请重新打开软件!");
        //this->close();
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
    ui->openButton->setEnabled(false);
    if(ui->openButton->text()==tr("打开串口"))
    {
        lockflag = false;
        workerThread->unlock(ui->PortBox->currentText());
        //关闭PortBox使能
        ui->lineEdit_id_1->setEnabled(false);
        ui->PortBox->setEnabled(false);
        ui->openButton->setText(tr("关闭串口"));
        ui->flaglabel_1->setStyleSheet("background-color:green;");


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
         ui->flaglabel_1->setStyleSheet("background-color:red;");
         //close database
         if(database.isOpen() && lockflag && lockflag_2){
             database.close();
         }

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
        ui->flaglabel_2->setStyleSheet("background-color:green;");



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
        ui->flaglabel_2->setStyleSheet("background-color:red;");
         //close database
        if(database.isOpen() && lockflag && lockflag_2){
            database.close();
        }
    }
    ui->openButton_2->setEnabled(true);
}

void MainWindow::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy年MM月dd日dddd hh时mm分");
    //QString str_2 = time.toString("hh时mm分");
    ui->labelTime->setText(str);
    //ui->labelTime_2->setText(str_2);
}
