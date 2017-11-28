#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QThread>
//#include <QDebug>




class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(QObject *parent);
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


#endif // WORKERTHREAD_H
