#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "workerthread.h"
#include "workerthread_2.h"



namespace Ui {
class MainWindow;

}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void mysql_init();


private:
    Ui::MainWindow *ui;
    bool lockflag = true;
    bool lockflag_2 = true;
    //bool dbflag = true;
    WorkerThread *workerThread;
    WorkerThread_2 *workerThread_2;
    QSqlDatabase database;

    int error_count = 0;
    bool wifi_cut_flag=false;
    bool is_wrong_passwd = false;
    QString text;


private slots:
    void on_openButton_clicked();
    void chulidata(char* buf);
    void on_openButton_2_clicked();
    void chulidata_2(char* buf);
    void timerUpdate(void);

    void on_wifiOpenButton_clicked();
   // void sleep(unsigned int msecs);

//signals:
 //   void resultReady(QSerialPort *serial);

};

#endif // MAINWINDOW_H
