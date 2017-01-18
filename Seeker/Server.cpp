#include "Server.h"

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

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
}

void Server::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        processTheDatagram(datagram, sender, senderPort);
    }
}

void Server::processTheDatagram(QByteArray datagram,  QHostAddress senderAddress, HostPort senderPort)
{
    QByteArray typeField( datagram.left(8) );
    Request *request;
    ActiveClients *clients = new ActiveClients();
    //ActiveClients::startCheckHello();
    if( typeField == QByteArray("REGISTER") ){
        //qDebug()<<"Register recived\n";
        request = new RegisterRequest();
    }
    else if( typeField == QByteArray("HELLO---") ) {
        request = new HelloRequest();
    }
    else if( typeField == QByteArray("SEEK----") ) {
        request = new SeekRequest();
    }
    else
        return;

    if( !request->setData(datagram, senderAddress, senderPort) )
        return;
    request->processRequest(clients);
}


