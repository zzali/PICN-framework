#include "SeekRequest.h"

#include "PublisherFinder.h"
#include "ActiveClients.h"
#include <QUdpSocket>
#include <iostream>
#include <QTime>

SeekRequest::SeekRequest()
{

}

SeekRequest::~SeekRequest()
{

}

bool SeekRequest::processRequest(ActiveClients *clients)
{
    if( payload.size() != 8 )
        return false;
    ContentKey contentKey = payload.mid(0, 8);
    //zz{
    //qDebug()<<"Seek request recieved for "<<contentKey<<"\n";
    //zz}
    bool ok;
    ClientID clientID = PublisherFinder::getInstance()->seekContent(clients,contentKey, ok);

    QUdpSocket socket;
    if(ok == false) {
        socket.writeDatagram(QByteArray("NOT FOUND"),client.getIp(), client.getPort());
        qDebug()<<"Not Found for content: "<<contentKey<<", time: "<<QTime::currentTime().msecsSinceStartOfDay()<<"\n";
        return false;
    }

    Client responderClient = clients->getClient(clientID);
    socket.writeDatagram(QByteArray::number(clientID, 16).rightJustified(8, '0')
                         + responderClient.getIp().toString().toLatin1(),
                         client.getIp(), client.getPort());
    qDebug()<<"Seeker Found for content: "<<contentKey<<", time: "<<QTime::currentTime().msecsSinceStartOfDay()<<"\n";
    return true;
}
