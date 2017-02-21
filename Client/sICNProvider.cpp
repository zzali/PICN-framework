 #include "sICNProvider.h"
#include "math.h"
#include <iostream>
#include <QMutex>
#include <QUdpSocket>
#include <QtDebug>

sICNProvider::sICNProvider(QObject *parent) :
    QObject(parent)
{
    provider = new Provider();
    headerFile = NULL;
    contentFile = NULL;
}

sICNProvider::~sICNProvider()
{
    //if(provider != NULL)
    //    delete provider;
    if(headerFile != NULL)
        delete headerFile;
    if(contentFile != NULL)
        delete contentFile;
}

void sICNProvider::disconnectFromBrowser()
{
    if(clientSocket != NULL) {
        if(clientSocket->isOpen())
            clientSocket->close();
        clientSocket->disconnectFromHost();
        delete clientSocket;
        clientSocket = NULL;
    }
    //qDebug()<<"sICNProvider::disconnectFromBrowser()\n";
}

void sICNProvider::setReceiverSocket(QTcpSocket *clientSocket)
{
    this->clientSocket = clientSocket;
}

bool sICNProvider::deliver(Request *request)
{

    if(deliverFromLocalRepository(request) == true){
        //zz{
        qDebug().noquote().nospace()<< qSetFieldWidth(10) << left << "LPICN"<< request->requestTime.msecsSinceStartOfDay()
                                    <<request->requestTime.msecsTo(request->firstByteTime)<<request->contentType << request->contentKey
                                   <<request->size<<request->requestTime.msecsTo(QTime::currentTime())<<qSetFieldWidth(0)<<"\n";
        //zz}
        return true;
    }
    //zz if( true || rand()%100 < Definitions::getInstance()->useICNPercentage) {
    if( true || qrand()%100 < Definitions::getInstance()->useICNPercentage) {
        bool success = false;
        QUdpSocket udpSocket;
        //zz{
        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());
        while(!udpSocket.bind(qrand()%(65535-1023)+1023));
        //zz}
        //qDebug()<<"Time before seek content "<<request->contentKey<<"is "<<QTime::currentTime().msecsSinceStartOfDay()<<"\n";
        udpSocket.writeDatagram(QByteArray("SEEK----")
                                + Definitions::getInstance()->clientID
                                + request->contentKey
                                , QHostAddress(Definitions::getInstance()->seekerIP)
                                , Definitions::getInstance()->seekerPort);
        if(udpSocket.waitForReadyRead(-1) == true) {
            //qDebug()<<"Time After waitForReadyRead for "<<request->contentKey<<"is "<<QTime::currentTime().msecsSinceStartOfDay()<<"\n";
            if(udpSocket.hasPendingDatagrams()) {
                //zz
                //qDebug()<<"sICNProvider::deliver, in (udpSocket.hasPendingDatagrams()\n";
                //zz
                QByteArray datagram;
                datagram.resize(udpSocket.pendingDatagramSize());
                QHostAddress sender;
                quint16 senderPort;
                udpSocket.readDatagram(datagram.data(), datagram.size(),
                                        &sender, &senderPort);

                //checking validity of sender
//                if(sender.toString() != Definitions::getInstance()->seekerIP
//                        || senderPort != Definitions::getInstance()->seekerPort)
//                    return false;

                if(datagram == "NOT FOUND"){
                   return false;
                }
                QString publisherIP = datagram.mid(8);

                provider->setPeerAddress(publisherIP, Definitions::getInstance()->publisherPort);
                //qDebug()<<"Time befor provider->deliver for "<<request->contentKey<<"is "<<request->requestTime.msecsTo(QTime::currentTime())<<"\n";
                if( provider->deliver(request, clientSocket) ) {
                    success = true;
                    //zz{
                    qDebug().noquote().nospace()<< qSetFieldWidth(10) << left << "PICN"<< request->requestTime.msecsSinceStartOfDay()
                               <<request->requestTime.msecsTo(request->firstByteTime) << request->contentType<<request->contentKey <<request->size
                               <<request->requestTime.msecsTo(QTime::currentTime())<<qSetFieldWidth(0)<<"\n";
                    //zz}
                    return true;
                }
            }
            else {
                return false;
            }
        }
        else{
            //mutex.unlock();
            return false;
        }
    }
    return false;

}

bool sICNProvider::deliverFromLocalRepository(Request *request)
{

    request->firstByteTime = QTime::currentTime();
    QString headerName = Definitions::getInstance()->cacheDir + request->hash + ".header";
    QString contentName = Definitions::getInstance()->cacheDir + request->hash + ".content";
    //qDebug()<<"deliverFromLocalRepository(): headerName: \n"<<headerName.toStdString()<<"\n";
    headerFile = new QFile(headerName);
    contentFile = new QFile(contentName);
    //zz{
    request->size = 0;
    //zz}
    if(headerFile->open(QIODevice::ReadOnly)) {
        while(!headerFile->atEnd()) {
            //zz clientSocket->write(headerFile->read(1000));
            request->size += clientSocket->write(headerFile->read(sICNProvider::MAX_READ_SIZE));
            clientSocket->flush();
        }
    }
    else
        return false;

    if(contentFile->open(QIODevice::ReadOnly)) {
        while(!contentFile->atEnd()) {
            //zz clientSocket->write(contentFile->read(1000));
            request->size += clientSocket->write(contentFile->read(sICNProvider::MAX_READ_SIZE));
            clientSocket->flush();
            this->thread()->msleep(3);
        }
        contentFile->close();
        if(clientSocket->state() != QTcpSocket::UnconnectedState)
            clientSocket->waitForBytesWritten(3000);

        return true;
    }
    else {
        return false;
        //zz return true; ///here we changed something
    }
}
