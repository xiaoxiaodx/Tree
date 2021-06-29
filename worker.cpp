#include "worker.h"
#include <QThread>
Worker::Worker(QObject *parent) : QObject(parent),isstart(false)
{

}

void Worker::slot_dowork(){



    isstart = true;
    while (isstart) {

        QThread::msleep(100);

        emit signal_timeout();
    }

}

Worker::~Worker(){
    isstart = false;
}
