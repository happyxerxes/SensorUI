#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include"workerthread.h"




class WorkerThread : public QThread
{
    Q_OBJECT
public:
    WorkerThread(QObject *parent);


    void lock(int i);
    void unlock(int i);
    void sendId(QString id,int num);
    void sql_init(QString passwd);


protected:

    virtual void run();
    bool lockFlag[2];
    bool allLockFlag = true;
    QString id[2];

    QSqlDatabase database;

signals:
    void resultReady(float* data);


};


#endif // WORKERTHREAD_H
