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

bool sICNProvider::deliver(Request request)
{

    if(deliverFromLocalRepository(request) == true){
        //zz{
        //qDebug()<<"deliver content from local repository\n";
        //zz}
        return true;
    }
    //zz if( true || rand()%100 < Definitions::getInstance()->useICNPercentage) {
    //zz{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    //zz}
    if( true || qrand()%100 < Definitions::getInstance()->useICNPercentage) {
        bool success = false;
        QUdpSocket udpSocket;
        //zz{
        while(!udpSocket.bind(qrand()%(65535-1023)+1023));
        //zz}
        udpSocket.writeDatagram(QByteArray("SEEK----")
                                + Definitions::getInstance()->clientID
                                + request.contentKey
                                , QHostAddress(Definitions::getInstance()->seekerIP)
                                , Definitions::getInstance()->seekerPort);
        //zz{
        //qDebug()<<"send seek request\n";
        //zz}
        if(udpSocket.waitForReadyRead(10000) == true) {
            //zz{
            //qDebug()<<"sICNProvider::deliver, Seek reply for "<<request.contentKey.toStdString()<<"\n";
            //zz}
            if(udpSocket.hasPendingDatagrams()) {
                //zz
                //qDebug()<<"sICNProvider::deliver, in (udpSocket.hasPendingDatagrams()\n";
                //zz
                QByteArray datagram;
                datagram.resize(udpSocket.pendingDatagramSize());
                QHostAddress sender;
                quint16 senderPort;
                //zz
                //qDebug()<<"sICNProvider::deliver, before readDatagram\n";
                //zz
                udpSocket.readDatagram(datagram.data(), datagram.size(),
                                        &sender, &senderPort);
                //zz
                //qDebug()<<"SEEK: sICNProvider::deliver, after readDatagram\n";
                //zz
                //checking validity of sender
//                if(sender.toString() != Definitions::getInstance()->seekerIP
//                        || senderPort != Definitions::getInstance()->seekerPort)
//                    return false;

                if(datagram == "NOT FOUND"){
                    //zz{
                    //qDebug()<<"SEEK: Seek Not found reply \n";
                    //zz}
                    return false;
                }
                //qDebug()<<"SEEK: Seek Found reply: "<<request.contentKey<<"\n";
                QString publisherIP = datagram.mid(8);

                provider->setPeerAddress(publisherIP, Definitions::getInstance()->publisherPort);
                if( provider->deliver(request, clientSocket) ) {
                    success = true;
                    //zz{
                    //qDebug() << "Seek: Deliver successfully from a peer for content \n";
                            //<< request.contentKey << endl;
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

bool sICNProvider::deliverFromLocalRepository(Request request)
{
    QString headerName = Definitions::getInstance()->cacheDir + request.hash + ".header";
    QString contentName = Definitions::getInstance()->cacheDir + request.hash + ".content";
    //qDebug()<<"deliverFromLocalRepository(): headerName: \n"<<headerName.toStdString()<<"\n";
    headerFile = new QFile(headerName);
    contentFile = new QFile(contentName);
    if(headerFile->open(QIODevice::ReadOnly)) {
        while(!headerFile->atEnd()) {
            clientSocket->write(headerFile->read(1000));
            clientSocket->flush();
        }
    }
    else
        return false;

    if(contentFile->open(QIODevice::ReadOnly)) {
        while(!contentFile->atEnd()) {
            clientSocket->write(contentFile->read(1000));
            clientSocket->flush();
            this->thread()->msleep(3);
        }
        contentFile->close();
        if(clientSocket->state() != QTcpSocket::UnconnectedState)
            clientSocket->waitForBytesWritten(3000);
        return true;
    }
    else {
        return true; ///here we changed something
    }
}
