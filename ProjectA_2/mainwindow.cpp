#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <qdatetime.h>
#include <QMessageBox>
#include <QInputDialog>

//备份输出
float backup_data[4]={624,5.40,668,4.34};

//检查数据库是否没变化
float previou_data[4];
int repeat_count[2];


//生成随机数0--n  配合qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
int generateRandomNumber(int n)
{
    return (qrand()%(n+1));
}

void init_UI(Ui::MainWindow *ui){

    ui->wifiOpenButton->setEnabled(false); ui->wifiOpenButton->setText("正常连接");
    ui->flaglabel_dbstatus->setStyleSheet("border-radius:10px;background-color:green;");

    ui->flaglabel_1->clear();
    ui->flaglabel_1->setStyleSheet("border-radius:8px;background-color:red;");
    ui->flaglabel_2->clear();
    ui->flaglabel_2->setStyleSheet("border-radius:8px;background-color:red;");

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
    text = QInputDialog::getText(NULL, "提示",
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

    //重新连接
    if(data[4] == 99){
        //qDebug() << "kick";
       workerThread->sql_init(text);
       qDebug() << "reconnect";
       wifi_cut_flag = false;
       workerThread->reset_wifi_cut_flag();

       ui->wifiOpenButton->setEnabled(false); ui->wifiOpenButton->setText(tr("正常连接"));
       ui->flaglabel_dbstatus->setStyleSheet("border-radius:10px;background-color:green;");

       data[4] = 0;

    }


    if(data[4] != 0 && wifi_cut_flag == false){
        wifi_cut_flag=true;
        if(data[4]==1){
           //QMessageBox::information(this,"提示1","网络连接错误，请检查网络后重新连接数据库!");
        }

        if(data[4]==2){
           QMessageBox::information(this,"提示2","数据库密码错误，请重启软件后输入正确密码!");
           this->close();
        }
        //wifiOpenButton
        ui->wifiOpenButton->setEnabled(false); ui->wifiOpenButton->setText(tr("重新连接"));
        ui->flaglabel_dbstatus->setStyleSheet("border-radius:10px;background-color:red;");
        //this->close();
    }

/*
    //断网时随机显示
    if(wifi_cut_flag == true){
        qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
        for(int i = 0; i<3; i=i+2){
            data[i+0]=backup_data[i+0]+generateRandomNumber(2);
            data[i+1]=backup_data[i+1]+0.01*generateRandomNumber(10);
        }
    }
*/

    for(int i=0; i<4; i++){
        previou_data[i]=data[i];
    }

    //断网时显示最后一次数值
    if(wifi_cut_flag == true){

        for(int i = 0; i<3; i=i+2){
            data[i+0]=previou_data[i+0];
            data[i+1]=previou_data[i+1];

        }
    }
/*
    //检查数据库是否没变化
    for(int i = 0; i<3; i=i+2){
        if(data[i+0]==previou_data[i+0] && data[i+1]==previou_data[i+1])
        {
            repeat_count[i/2]++;
        }
        else{
            repeat_count[i/2]=0;
        }

        for(int i=0; i<4; i++){
            previou_data[i]=data[i];
        }

        for(int i=0; i<4; i++){
            if(repeat_count[i] == 5){
                data[i*2+0] += generateRandomNumber(2);
                data[i*2+1] += 0.01*generateRandomNumber(10);

            }
        }

    }
*/
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
        ui->flaglabel_1->setStyleSheet("border-radius:8px;background-color:green;");


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
        ui->flaglabel_1->setStyleSheet("border-radius:8px;background-color:red;");



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
        ui->flaglabel_2->setStyleSheet("border-radius:8px;background-color:green;");


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
        ui->flaglabel_2->setStyleSheet("border-radius:8px;background-color:red;");
    }
}


void MainWindow::on_wifiOpenButton_clicked(){
    qDebug() << "kick";
    workerThread->sql_init(text);

    wifi_cut_flag = false;
    workerThread->reset_wifi_cut_flag();

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
