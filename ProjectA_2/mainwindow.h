#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "workerthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    bool lockflag[2];
    WorkerThread *workerThread;

    bool wifi_cut_flag = false;
    QString text;//password

private slots:
    void on_openButton_1_clicked();
    void on_openButton_2_clicked();

    void on_wifiOpenButton_clicked();



    void chulidata(float* data);

    void timerUpdate(void);
};

#endif // MAINWINDOW_H
