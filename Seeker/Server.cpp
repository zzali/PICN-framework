#include "Server.h"
#include "ProcessDatagramThread.h"

int readCount = 0;
Server::Server(QObject *parent)
    :QObject(parent)
{
    initSocket();
}

Server::~Server()
{

}

void Server::initSocket()
{
    udpSocket = new QUdpSocket;
    udpSocket->bind(QHostAddress(Definitions::globalInstance()->seekerIP), Definitions::globalInstance()->serverUdpPort);
//    udpSocket->bind(QHostAddress("127.0.0.1"), 7070);

    readCount = 0;

    while (udpSocket->waitForReadyRead(-1)) {
        while(udpSocket->hasPendingDatagrams()) {
                //qDebug()<<"Begin readPendingDatagrams #"<<readCount<<", time: "<<QTime::currentTime().second()<<"."<<QTime::currentTime().msec()<<"\n";
                QByteArray datagram;
                datagram.resize(udpSocket->pendingDatagramSize());
                QHostAddress sender;
                quint16 senderPort;

                udpSocket->readDatagram(datagram.data(), datagram.size(),
                                        &sender, &senderPort);
                ProcessDatagramThread *pd_thread = new ProcessDatagramThread();
                pd_thread->init(datagram, sender, senderPort);
                pd_thread->start();
            }
    }

}


