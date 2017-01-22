#include "RequestHandlerThread.h"
#include <iostream>

//#define DBG

RequestHandlerThread::RequestHandlerThread(QObject *parent) :
    QThread(parent)
{
    this->socket = NULL;
    this->hProvider = NULL;
    this->accessManager = NULL;
}

RequestHandlerThread::~RequestHandlerThread()
{
    if(hProvider != NULL) {
        delete hProvider;
        hProvider = NULL;
    }

}

void RequestHandlerThread::init(QTcpSocket *socket, Request *request)
{
    this->request = request;
    this->socket = socket;
    socket->moveToThread(this);

    accessManager = new QNetworkAccessManager();
    accessManager->moveToThread(this);
    hProvider = new HTTPProvider();
    hProvider->moveToThread(this);
    sProvider = new sICNProvider();
    sProvider->moveToThread(this);
//    serverSocket = new QTcpSocket();
//    serverSocket->moveToThread(this);
}

void RequestHandlerThread::run()
{
    //#ifdef DBG
    //    qDebug() << "Peer: " << socket->peerAddress().toString() << ":" << socket->peerPort() << endl;
    //    qDebug() << QString(request_txt) << endl;
    //#endif


    /// here I modified
    if( request->isFetchable() ) {
        //zz{
        //qDebug()<<"Start fetching from sProvider\n";
        //zz}
        sProvider->setReceiverSocket(socket);
        if(sProvider->deliver(request)) {
            //zz{
            //qDebug()<<"sProvider->deliver is Ok for content "<<request->contentKey<<"\n";
            //zz}
            sProvider->disconnectFromBrowser();
            delete sProvider;
            return;
        }
        delete sProvider;
        //zz{
        //qDebug()<<"sProvider->deliver failed for content "<<request->contentKey<<"\n";
        //zz}
    }
    //qDebug()<<"begin pureHttp\n";
    //zz}

    hProvider->setReceiverSocket(socket, accessManager);
    hProvider->startConnection(request);

    this->exec();
}
