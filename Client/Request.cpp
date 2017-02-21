#include "Request.h"

#include <QByteArray>

bool Request::setData(const QByteArray &datagram, QHostAddress &senderAddress, HostPort &senderPort)
{
    bool ok;

    client.setIp(senderAddress);
    client.setPort(senderPort);
    client.setId( datagram.mid(8, 8).toUInt(&ok, 16) );          // x.rightJustified(8, '0');

    if(ok != true)
        return false;

    payload = datagram.mid(16);

    return true;
}
Request::Request()
{
    
}

Request::~Request()
{
    
}
