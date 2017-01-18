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
    delete h;
//    PublisherThread *sndr = (PublisherThread*)sender();
//    socket->waitForDisconnected();
//    this->thread()->msleep(100);
//    sndr->wait();
//    if(sndr != NULL)
//        delete sndr;
//    if(socket != NULL)
//        delete socket;
}
