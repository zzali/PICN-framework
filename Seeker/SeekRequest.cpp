#include "SeekRequest.h"

#include "PublisherFinder.h"
#include "ActiveClients.h"
#include <QUdpSocket>
#include <iostream>

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
    //qDebug()<<"Seek request recieved for content \n";//<<contentKey<<"\n";
    //zz}
    bool ok;
    ClientID clientID = PublisherFinder::getInstance()->seekContent(clients,contentKey, ok);

    QUdpSocket socket;
    if(ok == false) {
        socket.writeDatagram(QByteArray("NOT FOUND"),client.getIp(), client.getPort());
            //qDebug()<<"Seeker error in sending <NOT FOUND>\n";
        //zz{
        qDebug()<<"Seeker Not found content "<<contentKey<<"\n";
        //zz}
        return false;
    }

    Client responderClient = clients->getClient(clientID);
    //zz{
    qDebug()<<"Seeker find a publisher clinet for "<<contentKey<<"\n";
    //zz}
    socket.writeDatagram(QByteArray::number(clientID, 16).rightJustified(8, '0')
                         + responderClient.getIp().toString().toLatin1(),
                         client.getIp(), client.getPort());
        //qDebug()<<"Seeker error in sending seek reply \n";
    return true;
}
