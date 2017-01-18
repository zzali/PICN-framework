#include "ProxyServer.h"
#include <math.h>
#include <iostream>

ProxyServer::ProxyServer(QObject *parent) :
    QObject(parent)
{
    idCount = 0;
    connectionCounter = 0;
    lastTime = 0;
    server = new QTcpServer(this);
    server->listen(QHostAddress("127.0.0.1"), Definitions::getInstance()->proxyPort);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnectionArrived()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(takeFromQueue()));
    timer->start(2);

    timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(takeFromQueue2()));
    timer2->start(20);
}

ProxyServer::~ProxyServer()
{
    if(server != NULL)
        delete server;
    if(timer != NULL)
        delete timer;
    if(timer2 != NULL)
        delete timer2;
}

void ProxyServer::newConnectionArrived()
{
//    qDebug() << connectionCounter;

    QTcpSocket *s = server->nextPendingConnection();
    //zz{
    //qDebug() << s->peerAddress() << ":" << s->peerPort() <<"\n";
    //zz}
    s->setParent(0);

    QByteArray request_txt;
    if(s->waitForReadyRead(500)) {
        request_txt = s->readAll();
    }
    else{
        return;
    }

    Request *request = new Request();
    //zz{
    //qDebug()<<"#Parsing request in ConnectionArrived\n";
    //zz}
    if( !request->parseRequest(request_txt))
        return;

    RequestHandlerThread *h = new RequestHandlerThread();
    h->init(s, request);
    connect(h, &QThread::finished, this, &ProxyServer::freeMemory);


    if( !request->isSupported() ) {
        Q.append(h);
        return;
    } else {
        Q2.append(h);
        return;
    }
}

void ProxyServer::freeMemory()
{
    RequestHandlerThread *sndr = (RequestHandlerThread*)sender();
//    if(idMap.contains(sndr->id)) {
//        idMap[sndr->id] --;
////        qDebug() << "minus -> id= " << sndr->id << " cnt= " << idMap[sndr->id];
//    }
////    if(sndr->request->isFetchable())
    connectionCounter --;
    delete sndr;
}

void ProxyServer::takeFromQueue()
{
    if(Q.size() == 0)
        return;
    else {
        connectionCounter ++;
        RequestHandlerThread* h = Q.front();
        Q.pop_front();
        h->start();
    }
}

void ProxyServer::takeFromQueue2()
{
    if(Q2.size() == 0)
        return;
    else {
        connectionCounter ++;
        RequestHandlerThread* h = Q2.front();
        Q2.pop_front();
        h->start();
    }
}
