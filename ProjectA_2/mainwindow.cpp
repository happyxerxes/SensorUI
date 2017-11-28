#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <qdatetime.h>
#include <QMessageBox>
#include <QInputDialog>

void init_UI(Ui::MainWindow *ui){
    ui->flaglabel_1->clear();
    ui->flaglabel_1->setStyleSheet("background-color:red;");
    ui->flaglabel_2->clear();
    ui->flaglabel_2->setStyleSheet("background-color:red;");

    ui->label_25->setVisible(false);
    ui->labelTime->setVisible(false);
    ui->textEdit_3->setVisible(false);
    ui->textEdit_4->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->textEdit_1->setVisible(false);

    ui->textEdit_3->setFont(QFont("Timers" , 24 ,  QFont::Bold));
    ui->textEdit_4->setFont(QFont("Timers" , 20 ,  QFont::Bold));
    ui->labelTime->setFont(QFont("Timers" , 12 ,  QFont::Bold));
    ui->labelTime_2->setFont(QFont("Timers" , 12 ,  QFont::Bold));

    ui->textEdit_1->setFont(QFont("Timers" , 20 ,  QFont::Bold));
    ui->textEdit_2->setFont(QFont("Timers" , 20 ,  QFont::Bold));

    ui->lineEdit_co2_1->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_co2_2->setFocusPolicy(Qt::NoFocus);



    ui->lineEdit_fs_1->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_fs_2->setFocusPolicy(Qt::NoFocus);




    ui->lineEdit_co2_1->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_co2_2->setFont(QFont("Timers" , 28 ,  QFont::Bold));


    ui->lineEdit_fs_1->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    ui->lineEdit_fs_2->setFont(QFont("Timers" , 28 ,  QFont::Bold));

    ui->lineEdit_id_1->setFont(QFont("Timers" , 26 ,  QFont::Bold));
    ui->lineEdit_id_2->setFont(QFont("Timers" , 26 ,  QFont::Bold));

    ui->lineEdit_id_1->setText("A1");
    ui->lineEdit_id_2->setText("A2");
    ui->lineEdit_id_1->setEnabled(false);
    ui->lineEdit_id_2->setEnabled(false);
    ui->label_03->setVisible(false);
    ui->label_07->setVisible(false);
    ui->lineEdit_id_1->setVisible(false);
    ui->lineEdit_id_2->setVisible(false);



    ui->textEdit_2->setFont(QFont("Timers" , 30 ,  QFont::Bold));
    ui->textEdit_1->setFont(QFont("Timers" , 30 ,  QFont::Bold));




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
    for(int i=0;i<2;i++){
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

    if(data[4]==1 && wifi_cut_flag == 1){
        wifi_cut_flag=0;
        QMessageBox::information(this,"提示","网络断开，请重新打开软件!");
        this->close();
    }

    int i=0;
    if(lockflag[0]==false){
        QString str = QString::number(data[i+0], 'f', 0);
        ui->lineEdit_co2_1->clear();
        ui->lineEdit_co2_1->insert(str);
        str = QString::number(data[i+1], 'f', 2);
        ui->lineEdit_fs_1->clear();
        ui->lineEdit_fs_1->insert(str);
    }
    i=i+2;
    if(lockflag[1]==false){
        QString str = QString::number(data[i+0], 'f', 0);
        ui->lineEdit_co2_2->clear();
        ui->lineEdit_co2_2->insert(str);
        str = QString::number(data[i+1], 'f', 2);
        ui->lineEdit_fs_2->clear();
        ui->lineEdit_fs_2->insert(str);
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
        ui->lineEdit_fs_1->clear();


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
        ui->lineEdit_fs_2->clear();

        //恢复lineEdit_id使能
       // ui->lineEdit_id_2->setEnabled(true);
        ui->openButton_2->setText(tr("开始读取"));
        ui->flaglabel_2->setStyleSheet("background-color:red;");
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
