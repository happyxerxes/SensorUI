#include "workerthread.h"

WorkerThread::WorkerThread(QObject *parent) :
    QThread(parent)
{


}

void WorkerThread::run()
{
    char data[8]={0x01,0x03,0x00,0x00,0x00,0x05,0x85,0xC9};
    char buf[15];

    while(1){
        //qDebug() << lockFlag;
         if(lockFlag == false){

             serial = new QSerialPort(this);
             serial->setPortName(portName);
             serial->open(QIODevice::ReadWrite);
             serial->setBaudRate(QSerialPort::Baud9600);
             serial->setDataBits(QSerialPort::Data8);
             serial->setParity(QSerialPort::NoParity);
             serial->setStopBits(QSerialPort::OneStop);
             serial->setFlowControl(QSerialPort::NoFlowControl);
             while(1)
             {
                  if(lockFlag == true){break;}

                  serial->write(data,8);
                  msleep(1000);
                  if(serial->waitForReadyRead(100) == true){
                       if(serial->read(buf,15) == 15){
                           if(buf[0]==0x01 && buf[1]==0x03 && buf[2]==0x0A ){
                               emit resultReady(buf);
                               //qDebug() << 111;
                           }
                       }
                   }
             }
             //关闭串口
             serial->clear();
             serial->close();
             serial->deleteLater();
         }
    }





}

void WorkerThread::lock(){
    lockFlag = true;

}
void WorkerThread::unlock(QString com){
    portName = com;
    lockFlag = false;
     //qDebug() << lockFlag;
}


