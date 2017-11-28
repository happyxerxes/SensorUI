#include "workerthread_2.h"

#include <qDebug.h>;

WorkerThread_2::WorkerThread_2(QObject *parent) :
    QThread(parent)
{


}

void WorkerThread_2::run()
{
   // char data[8]={0x01,0x03,0x00,0x00,0x00,0x05,0x85,0xC9};
     char buf[7];

    while(1){
         if(lockFlag == false){
             serial = new QSerialPort(this);
             //connect(serial,SIGNAL(readyRead()),this,SLOT(updata()));

             serial->setPortName(portName);
             serial->open(QIODevice::ReadWrite);
             serial->setBaudRate(QSerialPort::Baud115200);
             serial->setDataBits(QSerialPort::Data8);
             serial->setParity(QSerialPort::NoParity);
             serial->setStopBits(QSerialPort::OneStop);
             serial->setFlowControl(QSerialPort::NoFlowControl);

             while(1)
             {
                  if(lockFlag == true){break;}
                //  qDebug() << 222;
                //  serial->write(data,8);
                  serial->readAll();
                  if(serial->waitForReadyRead(100) == true){
                       if(serial->read(buf,7) == 7){
                           if(buf[0]==0x72&&buf[5]==0x0D&&buf[6]==0x0A){
                               emit resultReady(buf);
                               //qDebug() << (QString)buf[1];
                           }
                       }
                   }
                   msleep(800);
             }
             //关闭串口

             serial->clear();
             serial->close();
             serial->deleteLater();

         }
    }





}

void WorkerThread_2::lock(){
    lockFlag = true;
}
void WorkerThread_2::unlock(QString com){
    portName = com;
    lockFlag = false;
}

//void WorkerThread_2::updata(){}
