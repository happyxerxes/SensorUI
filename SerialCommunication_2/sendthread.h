#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include <QThread>
namespace Ui {
class SendThread;

}
class SendThread : public QThread
{
     Q_OBJECT
 private:
     void run();
 };


#endif // SENDTHREAD_H
