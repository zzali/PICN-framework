#include "PublisherServer.h"

PublisherServer::PublisherServer(QObject *parent) :
    QObject(parent)
{
    responseCount = 0;
    MAX_RESPONSE = 15;
    server = new QTcpServer(this);
    server->listen(QHostAddress(""), Definitions::getInstance()->publisherPort);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnectionArrived()));
}

//zz{
PublisherServer::~PublisherServer(){
    //delete h;
    if (h!=NULL){
        h->quit();
        if(!h->wait(1000)) //Wait until it actually has terminated (max. 3 sec)
        {
            h->terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
            qDebug()<<"before wait in ~publisherServer()\n";
            h->wait(); //We have to wait again here!
            qDebug()<<"after wait in ~publisherServer()\n";
        }
    }
    /*if (h!=NULL){
        h->wait(5000);
        delete h;
    }*/
}

//zz}

void PublisherServer::newConnectionArrived()
{
    socket = server->nextPendingConnection();
    socket->setParent(0);
    h = new PublisherThread();
    connect(h, &QThread::finished, this, &PublisherServer::freeMemory);
    responseCount ++;
    h->init(socket, responseCount < 15);
    h->start();
}

void PublisherServer::freeMemory()
{
    responseCount --;
    //zz delete h;
    if (h!=NULL){
        h->quit();
        if(!h->wait(3000)) //Wait until it actually has terminated (max. 3 sec)
        {
            h->terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
            qDebug()<<"Before wait in freeMemory()\n";
            h->wait(); //We have to wait again here!
            qDebug()<<"After wait in freeMemory()\n";
        }
    }

//    PublisherThread *sndr = (PublisherThread*)sender();
//    socket->waitForDisconnected();
//    this->thread()->msleep(100);
//    sndr->wait();
//    if(sndr != NULL)
//        delete sndr;
//    if(socket != NULL)
//        delete socket;
}
