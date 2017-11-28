#ifndef WORKERTHREAD_2_H
#define WORKERTHREAD_2_H


#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QThread>
//#include <QDebug>


class WorkerThread_2 : public QThread
{
    Q_OBJECT
public:
    WorkerThread_2(QObject *parent);
    QSerialPort *serial;

    void lock();
    void unlock(QString com);


protected:

    virtual void run();
    bool lockFlag = true;
    QString portName;

signals:
    void resultReady(char* buf);


};

#endif // WORKERTHREAD_2_H
