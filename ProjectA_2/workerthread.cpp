#include "workerthread.h"

#define ERRORCOUNT 10

WorkerThread::WorkerThread(QObject *parent) :
    QThread(parent)
{
    //lockFlag init
        for(int i=0;i<2;i++){
            lockFlag[i]=true;
        }

}

void WorkerThread::run()
{
    //char data[8]={0x01,0x03,0x00,0x00,0x00,0x05,0x85,0xC9};
    float data[5];
    data[4]=0;
    int error_count = 0;


    while(1){
         if(allLockFlag == false){

             //open database
             //bool r = database.open();
             //if (r){  qDebug() << "Connect OK!";}

             while(1)
             {
                 if(wifi_cut_flag == false){
                    //receive data from database
                    QSqlQuery sql_query;
                    QString update_sql = "select * from test where id = :id ";


                    for(int i=0;i<2;i++){
                        if(lockFlag[i] == false){
                            sql_query.prepare(update_sql);
                            sql_query.bindValue(":id", id[i]);
                            msleep(100);
                            if(sql_query.exec())
                            {
                                error_count=0;
                                sql_query.next();
                                data[2*i+0]= sql_query.value(4).toFloat();
                                data[2*i+1]= sql_query.value(6).toFloat();
                            }
                            else{error_count++;}

                            if(error_count > ERRORCOUNT){

                                //qDebug() << "error";
                                if(is_wrong_passwd){data[4] = 2;}
                                else{data[4] = 1;}

                                emit resultReady(data);
                                msleep(200);


                                data[4] = 0;
                                error_count=0;
                                wifi_cut_flag = true;
                                database.close();
                                //database->free();
                                break;
                                //while(1){for(int i=0;i<9999;i++);}
                            }


                        }
                    }

                    emit resultReady(data);


                    msleep(100);
                }

                //断网时
                else{
                     msleep(5000);
                     data[4] = 99;

                     emit resultReady(data);
                }


             }
             //close database
             //database.close();
         }
    }





}

void WorkerThread::lock(int i){
    lockFlag[i] = true;
    allLockFlag = true;
    for(int i=0;i<2;i++){
        if(lockFlag[i]==false){allLockFlag=false;}
    }
}
void WorkerThread::unlock(int i){
    allLockFlag = false;
    lockFlag[i] = false;
}

void WorkerThread::sendId(QString id,int num){
    this->id[num] = id;
}

void WorkerThread::sql_init(QString passwd){
    //mysql init
        if (QSqlDatabase::contains("qt_sql_default_connection"))
        {
            database = QSqlDatabase::database("qt_sql_default_connection");
        }
        else
        {
            database = QSqlDatabase::addDatabase("QMYSQL");
            //qDebug() << "MYSQL driver valid" << database.isValid();
            database.setHostName("123.206.24.89");
            database.setUserName("test");
            database.setPassword(passwd);
            database.setDatabaseName("test");
            database.setConnectOptions("MYSQL_OPT_CONNECT_TIMEOUT=2");
        }

        qDebug() <<"111";
        bool r=database.open();
        qDebug() << QString::number(r);

        //qDebug() <<"222";
        //qDebug() << database.lastError().nativeErrorCode();

        bool ok;
        int i = database.lastError().nativeErrorCode().toInt(&ok,10);
        if(i == 1045){
            is_wrong_passwd = true;
        }
        else {};
}

void WorkerThread::reset_wifi_cut_flag(){
    wifi_cut_flag=false;
}
