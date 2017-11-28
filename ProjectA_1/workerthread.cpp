#include "workerthread.h"

WorkerThread::WorkerThread(QObject *parent) :
    QThread(parent)
{


}

void WorkerThread::run()
{
    char data[9]={0x01,0x03,0x00,0x00,0x00,0x02,0xC4,0x0B,0x00};
    char buf[9];

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

                  serial->write(data,9);
                  msleep(1000);
                  if(serial->waitForReadyRead(100) == true){
                       if(serial->read(buf,9) == 9){
                           if(buf[0]==0x01 && buf[1]==0x03 && buf[2]==0x04 ){
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


