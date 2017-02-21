#include "PublisherThread.h"

PublisherThread::PublisherThread(QObject *parent) :
    QThread(parent)
{
    publisher = new Publisher();
}

PublisherThread::~PublisherThread()
{
    if(publisher != NULL)
        delete publisher;
    if(socket != NULL)
        delete socket;
}

void PublisherThread::run()
{
//    qDebug() << "here 10, PublisherThread";
    QByteArray request_txt;
    if(socket->waitForReadyRead(10000)) {
        request_txt = socket->readAll();
    }
    else{
        return;
    }
//    qDebug() << QString(request_txt) << "18";

    PeerRequest request;
    if(!request.parseRequest(request_txt))
        return;

//    qDebug() << QString(request.hash);

    bool success = false; //for nothing
    if(request.isFetchable() /*zz && ClientCore::getInstance()->isValidInRepository(request.hash)*/
                && responsePriority == 1) {
        publisher->setReceiverSocket(socket);
        if(publisher->deliver(request))
            success = true;
    }
    else {
        socket->write("NOT FOUND");
        socket->flush();
        //zz socket->waitForReadyRead(500);
        socket->disconnectFromHost();
    }
//    socket->waitForBytesWritten();
//    qDebug() << "file sent!";
//    socket->disconnectFromHost();
//    delete socket;

//    this->exec();
}

void PublisherThread::init(QTcpSocket *socket, int priority)
{
    this->responsePriority = priority;
    this->socket = socket;
    socket->moveToThread(this);
}
