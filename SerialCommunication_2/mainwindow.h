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

    bool lockflag[6];
    WorkerThread *workerThread;
    int wifi_cut_flag=1;

private slots:
    void on_openButton_1_clicked();
    void on_openButton_2_clicked();
    void on_openButton_3_clicked();
    void on_openButton_4_clicked();
    void on_openButton_5_clicked();
    void on_openButton_6_clicked();

    void chulidata(float* data);

    void timerUpdate(void);
};

#endif // MAINWINDOW_H
