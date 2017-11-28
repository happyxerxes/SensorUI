#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <qdatetime.h>
#include <QMessageBox>
#include <QInputDialog>

void init_UI(Ui::MainWindow *ui){

    ui->label_25->setVisible(false);
    ui->labelTime->setVisible(false);
    ui->lineEdit_id_1->setText("Ba1");
    ui->lineEdit_id_2->setText("Ba2");
    ui->lineEdit_id_3->setText("Bb1");
    ui->lineEdit_id_4->setText("Bb2");
    ui->lineEdit_id_5->setText("Bc1");
    ui->lineEdit_id_6->setText("Bc2");
    ui->lineEdit_id_1->setEnabled(false);
    ui->lineEdit_id_2->setEnabled(false);
    ui->lineEdit_id_3->setEnabled(false);
    ui->lineEdit_id_4->setEnabled(false);
    ui->lineEdit_id_5->setEnabled(false);
    ui->lineEdit_id_6->setEnabled(false);

    ui->flaglabel_1->clear();
    ui->flaglabel_1->setStyleSheet("background-color:red;");
    ui->flaglabel_2->clear();
    ui->flaglabel_2->setStyleSheet("background-color:red;");
    ui->flaglabel_3->clear();
    ui->flaglabel_3->setStyleSheet("background-color:red;");
    ui->flaglabel_4->clear();
    ui->flaglabel_4->setStyleSheet("background-color:red;");
    ui->flaglabel_5->clear();
    ui->flaglabel_5->setStyleSheet("background-color:red;");
    ui->flaglabel_6->clear();
    ui->flaglabel_6->setStyleSheet("background-color:red;");

    ui->lineEdit_id_1->setVisible(false);
    ui->lineEdit_id_2->setVisible(false);
    ui->lineEdit_id_3->setVisible(false);
    ui->lineEdit_id_4->setVisible(false);
    ui->lineEdit_id_5->setVisible(false);
    ui->lineEdit_id_6->setVisible(false);
    ui->lineEdit_id_1->setVisible(false);
    ui->lineEdit_id_2->setVisible(false);
    ui->lineEdit_id_3->setVisible(false);
    ui->lineEdit_id_4->setVisible(false);
    ui->lineEdit_id_5->setVisible(false);
    ui->lineEdit_id_6->setVisible(false);
    ui->label_12->setVisible(false);
    ui->label_13->setVisible(false);
    ui->label_14->setVisible(false);
    ui->label_15->setVisible(false);
    ui->label_16->setVisible(false);
    ui->label_17->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->nameLineEdit_1->setVisible(false);
    ui->nameLineEdit_2->setVisible(false);
    ui->nameLineEdit_3->setVisible(false);

    ui->labelTime->setFont(QFont("Timers" , 12 ,  QFont::Bold));
    ui->labelTime_2->setFont(QFont("Timers" , 12 ,  QFont::Bold));
    ui->textEdit_2->setFont(QFont("Timers" , 24 ,  QFont::Bold));
    ui->textEdit->setFont(QFont("Timers" , 20 ,  QFont::Bold));

    ui->lineEdit_co2_1->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_co2_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_co2_3->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_co2_4->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_co2_5->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_co2_6->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_wd_1->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_wd_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_wd_3->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_wd_4->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_wd_5->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_wd_6->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_sd_1->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_sd_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_sd_3->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_sd_4->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_sd_5->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_sd_6->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_gzd_1->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_gzd_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_gzd_3->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_gzd_4->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_gzd_5->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_gzd_6->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_dqyl_1->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_dqyl_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_dqyl_3->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_dqyl_4->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_dqyl_5->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_dqyl_6->setFocusPolicy(Qt::NoFocus);


    ui->lineEdit_co2_1->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_co2_2->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_co2_3->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_co2_4->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_co2_5->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_co2_6->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_wd_1->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_wd_2->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_wd_3->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_wd_4->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_wd_5->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_wd_6->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_sd_1->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_sd_2->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_sd_3->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_sd_4->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_sd_5->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_sd_6->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_gzd_1->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_gzd_2->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_gzd_3->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_gzd_4->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_gzd_5->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_gzd_6->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_dqyl_1->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_dqyl_2->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_dqyl_3->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_dqyl_4->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_dqyl_5->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_dqyl_6->setFont(QFont("Timers" , 28 ,  QFont::Bold));

    ui->lineEdit_id_1->setFont(QFont("Timers" , 26 ,  QFont::Bold));
    ui->lineEdit_id_2->setFont(QFont("Timers" , 26 ,  QFont::Bold));
    ui->lineEdit_id_3->setFont(QFont("Timers" , 26 ,  QFont::Bold));
    ui->lineEdit_id_4->setFont(QFont("Timers" , 26 ,  QFont::Bold));
    ui->lineEdit_id_5->setFont(QFont("Timers" , 26 ,  QFont::Bold));
    ui->lineEdit_id_6->setFont(QFont("Timers" , 26 ,  QFont::Bold));

    ui->nameLineEdit_1->setFont(QFont("Timers" , 30 ,  QFont::Bold));
    ui->nameLineEdit_2->setFont(QFont("Timers" , 30 ,  QFont::Bold));
    ui->nameLineEdit_3->setFont(QFont("Timers" , 30 ,  QFont::Bold));





}
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
//lockflag init
    for(int i=0;i<6;i++){
        lockflag[i] = true;
    }

//UI init
    init_UI(ui);


//workerThread init
    workerThread = new WorkerThread(this);
    connect(workerThread, SIGNAL(resultReady(float*)), this, SLOT(chulidata(float*)));
    workerThread->sql_init(text);
    workerThread->start();

//show time
    QTimer *timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chulidata(float* data){

    if(data[30]==1 && wifi_cut_flag == 1){
        wifi_cut_flag=0;
        QMessageBox::information(this,"提示","网络断开，请重新打开软件!");
        this->close();
    }

    int i=0;
    if(lockflag[0]==false){
        QString str = QString::number(data[i+0], 'f', 2);
        ui->lineEdit_wd_1->clear();
        ui->lineEdit_wd_1->insert(str);
        str = QString::number(data[i+1], 'f', 2);
        ui->lineEdit_sd_1->clear();
        ui->lineEdit_sd_1->insert(str);
        str = QString::number(data[i+2], 'f', 0);
        ui->lineEdit_gzd_1->clear();
        ui->lineEdit_gzd_1->insert(str);
        str = QString::number(data[i+3], 'f', 0);
        ui->lineEdit_co2_1->clear();
        ui->lineEdit_co2_1->insert(str);
        str = QString::number(data[i+4], 'f', 2);
        ui->lineEdit_dqyl_1->clear();
        ui->lineEdit_dqyl_1->insert(str);
    }
    i=i+5;
    if(lockflag[1]==false){
        QString str = QString::number(data[i+0], 'f', 2);
        ui->lineEdit_wd_2->clear();
        ui->lineEdit_wd_2->insert(str);
        str = QString::number(data[i+1], 'f', 2);
        ui->lineEdit_sd_2->clear();
        ui->lineEdit_sd_2->insert(str);
        str = QString::number(data[i+2], 'f', 0);
        ui->lineEdit_gzd_2->clear();
        ui->lineEdit_gzd_2->insert(str);
        str = QString::number(data[i+3], 'f', 0);
        ui->lineEdit_co2_2->clear();
        ui->lineEdit_co2_2->insert(str);
        str = QString::number(data[i+4], 'f', 2);
        ui->lineEdit_dqyl_2->clear();
        ui->lineEdit_dqyl_2->insert(str);
    }
    i=i+5;
    if(lockflag[2]==false){
        QString str = QString::number(data[i+0], 'f', 2);
        ui->lineEdit_wd_3->clear();
        ui->lineEdit_wd_3->insert(str);
        str = QString::number(data[i+1], 'f', 2);
        ui->lineEdit_sd_3->clear();
        ui->lineEdit_sd_3->insert(str);
        str = QString::number(data[i+2], 'f', 0);
        ui->lineEdit_gzd_3->clear();
        ui->lineEdit_gzd_3->insert(str);
        str = QString::number(data[i+3], 'f', 0);
        ui->lineEdit_co2_3->clear();
        ui->lineEdit_co2_3->insert(str);
        str = QString::number(data[i+4], 'f', 2);
        ui->lineEdit_dqyl_3->clear();
        ui->lineEdit_dqyl_3->insert(str);
    }
    i=i+5;
    if(lockflag[3]==false){
        QString str = QString::number(data[i+0], 'f', 2);
        ui->lineEdit_wd_4->clear();
        ui->lineEdit_wd_4->insert(str);
        str = QString::number(data[i+1], 'f', 2);
        ui->lineEdit_sd_4->clear();
        ui->lineEdit_sd_4->insert(str);
        str = QString::number(data[i+2], 'f', 0);
        ui->lineEdit_gzd_4->clear();
        ui->lineEdit_gzd_4->insert(str);
        str = QString::number(data[i+3], 'f', 0);
        ui->lineEdit_co2_4->clear();
        ui->lineEdit_co2_4->insert(str);
        str = QString::number(data[i+4], 'f', 2);
        ui->lineEdit_dqyl_4->clear();
        ui->lineEdit_dqyl_4->insert(str);
    }
    i=i+5;
    if(lockflag[4]==false){
        QString str = QString::number(data[i+0], 'f', 2);
        ui->lineEdit_wd_5->clear();
        ui->lineEdit_wd_5->insert(str);
        str = QString::number(data[i+1], 'f', 2);
        ui->lineEdit_sd_5->clear();
        ui->lineEdit_sd_5->insert(str);
        str = QString::number(data[i+2], 'f', 0);
        ui->lineEdit_gzd_5->clear();
        ui->lineEdit_gzd_5->insert(str);
        str = QString::number(data[i+3], 'f', 0);
        ui->lineEdit_co2_5->clear();
        ui->lineEdit_co2_5->insert(str);
        str = QString::number(data[i+4], 'f', 2);
        ui->lineEdit_dqyl_5->clear();
        ui->lineEdit_dqyl_5->insert(str);
    }
    i=i+5;
    if(lockflag[5]==false){
        QString str = QString::number(data[i+0], 'f', 2);
        ui->lineEdit_wd_6->clear();
        ui->lineEdit_wd_6->insert(str);
        str = QString::number(data[i+1], 'f', 2);
        ui->lineEdit_sd_6->clear();
        ui->lineEdit_sd_6->insert(str);
        str = QString::number(data[i+2], 'f', 0);
        ui->lineEdit_gzd_6->clear();
        ui->lineEdit_gzd_6->insert(str);
        str = QString::number(data[i+3], 'f', 0);
        ui->lineEdit_co2_6->clear();
        ui->lineEdit_co2_6->insert(str);
        str = QString::number(data[i+4], 'f', 2);
        ui->lineEdit_dqyl_6->clear();
        ui->lineEdit_dqyl_6->insert(str);
    }



}

void MainWindow::on_openButton_1_clicked(){
    int num=0;
    if(ui->openButton_1->text()==tr("开始读取"))
    {
        lockflag[num] = false;
        workerThread->unlock(num);
        workerThread->sendId(ui->lineEdit_id_1->text(),num);
        //关闭lineEdit_id使能
        ui->lineEdit_id_1->setEnabled(false);
        ui->openButton_1->setText(tr("结束读取"));
        ui->flaglabel_1->setStyleSheet("background-color:green;");

    }
    else
    {
        lockflag[num] = true;
        workerThread->lock(num);

        ui->lineEdit_co2_1->clear();
        ui->lineEdit_wd_1->clear();
        ui->lineEdit_sd_1->clear();
        ui->lineEdit_gzd_1->clear();
        ui->lineEdit_dqyl_1->clear();

        //恢复lineEdit_id使能
        //ui->lineEdit_id_1->setEnabled(true);
        ui->openButton_1->setText(tr("开始读取"));
        ui->flaglabel_1->setStyleSheet("background-color:red;");



    }
}
void MainWindow::on_openButton_2_clicked(){
    int num=1;
    if(ui->openButton_2->text()==tr("开始读取"))
    {
        lockflag[num] = false;
        workerThread->unlock(num);
        workerThread->sendId(ui->lineEdit_id_2->text(),num);
        //关闭lineEdit_id使能
        ui->lineEdit_id_2->setEnabled(false);
        ui->openButton_2->setText(tr("结束读取"));
        ui->flaglabel_2->setStyleSheet("background-color:green;");



    }
    else
    {
        lockflag[num] = true;
        workerThread->lock(num);

        ui->lineEdit_co2_2->clear();
        ui->lineEdit_wd_2->clear();
        ui->lineEdit_sd_2->clear();
        ui->lineEdit_gzd_2->clear();
        ui->lineEdit_dqyl_2->clear();

        //恢复lineEdit_id使能
        //ui->lineEdit_id_2->setEnabled(true);
        ui->openButton_2->setText(tr("开始读取"));
        ui->flaglabel_2->setStyleSheet("background-color:red;");
    }
}
void MainWindow::on_openButton_3_clicked(){
    int num=2;
    if(ui->openButton_3->text()==tr("开始读取"))
    {
        lockflag[num] = false;
        workerThread->unlock(num);
        workerThread->sendId(ui->lineEdit_id_3->text(),num);
        //关闭lineEdit_id使能
        ui->lineEdit_id_3->setEnabled(false);
        ui->openButton_3->setText(tr("结束读取"));
        ui->flaglabel_3->setStyleSheet("background-color:green;");

    }
    else
    {
        lockflag[num] = true;
        workerThread->lock(num);

        ui->lineEdit_co2_3->clear();
        ui->lineEdit_wd_3->clear();
        ui->lineEdit_sd_3->clear();
        ui->lineEdit_gzd_3->clear();
        ui->lineEdit_dqyl_3->clear();

        //恢复lineEdit_id使能
        //ui->lineEdit_id_3->setEnabled(true);
        ui->openButton_3->setText(tr("开始读取"));
        ui->flaglabel_3->setStyleSheet("background-color:red;");
    }
}
void MainWindow::on_openButton_4_clicked(){
    int num=3;
    if(ui->openButton_4->text()==tr("开始读取"))
    {
        lockflag[num] = false;
        workerThread->unlock(num);
        workerThread->sendId(ui->lineEdit_id_4->text(),num);
        //关闭lineEdit_id使能
        ui->lineEdit_id_4->setEnabled(false);
        ui->openButton_4->setText(tr("结束读取"));
        ui->flaglabel_4->setStyleSheet("background-color:green;");


    }
    else
    {
        lockflag[num] = true;
        workerThread->lock(num);

        ui->lineEdit_co2_4->clear();
        ui->lineEdit_wd_4->clear();
        ui->lineEdit_sd_4->clear();
        ui->lineEdit_gzd_4->clear();
        ui->lineEdit_dqyl_4->clear();

        //恢复lineEdit_id使能
        //ui->lineEdit_id_4->setEnabled(true);
        ui->openButton_4->setText(tr("开始读取"));
        ui->flaglabel_4->setStyleSheet("background-color:red;");
    }
}
void MainWindow::on_openButton_5_clicked(){
    int num=4;
    if(ui->openButton_5->text()==tr("开始读取"))
    {
        lockflag[num] = false;
        workerThread->unlock(num);
        workerThread->sendId(ui->lineEdit_id_5->text(),num);
        //关闭lineEdit_id使能
        ui->lineEdit_id_5->setEnabled(false);
        ui->openButton_5->setText(tr("结束读取"));
        ui->flaglabel_5->setStyleSheet("background-color:green;");


    }
    else
    {
        lockflag[num] = true;
        workerThread->lock(num);

        ui->lineEdit_co2_5->clear();
        ui->lineEdit_wd_5->clear();
        ui->lineEdit_sd_5->clear();
        ui->lineEdit_gzd_5->clear();
        ui->lineEdit_dqyl_5->clear();

        //恢复lineEdit_id使能
        //ui->lineEdit_id_5->setEnabled(true);
        ui->openButton_5->setText(tr("开始读取"));
        ui->flaglabel_5->setStyleSheet("background-color:red;");
    }
}
void MainWindow::on_openButton_6_clicked(){
    int num=5;
    if(ui->openButton_6->text()==tr("开始读取"))
    {
        lockflag[num] = false;
        workerThread->unlock(num);
        workerThread->sendId(ui->lineEdit_id_6->text(),num);
        //关闭lineEdit_id使能
        ui->lineEdit_id_6->setEnabled(false);
        ui->openButton_6->setText(tr("结束读取"));
        ui->flaglabel_6->setStyleSheet("background-color:green;");


    }
    else
    {
        lockflag[num] = true;
        workerThread->lock(num);

        ui->lineEdit_co2_6->clear();
        ui->lineEdit_wd_6->clear();
        ui->lineEdit_sd_6->clear();
        ui->lineEdit_gzd_6->clear();
        ui->lineEdit_dqyl_6->clear();

        //恢复lineEdit_id使能
        //ui->lineEdit_id_6->setEnabled(true);
        ui->openButton_6->setText(tr("开始读取"));
        ui->flaglabel_6->setStyleSheet("background-color:red;");
    }
}


void MainWindow::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    QString str = time.toString("yyyy年MM月dd日dddd hh时mm分");
    //QString str_2 = time.toString("hh时mm分");
    ui->labelTime->setText(str);
    //ui->labelTime_2->setText(str_2);
}
