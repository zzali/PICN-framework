#include "RepositoryCreatorThread.h"

RepositoryCreatorThread::RepositoryCreatorThread(QObject *parent) :
    QThread(parent)
{
}

void RepositoryCreatorThread::run()
{
    rc = new RepositoryCreator();
    RegisterServer = new RegisterRepository();
    rc->moveToThread(this);
    int cnt = 0;
    while(1) {
        cnt ++;
        this->msleep(50);
        rc->startProcess();
        if(cnt%40 == 0){
            rc->writeDownInfo();
            //zz{
            RegisterServer->sendUnRegistered();
            //zz}
        }

    }
}
