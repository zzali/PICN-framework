#ifndef REQUEST_H
#define REQUEST_H

#include "Definitions.h"
#include "Client.h"
#include <QHostAddress>

class Request
{
protected:
    Client client;
    QByteArray payload;


public:
    Request();
    ~Request();

    virtual bool processRequest() = 0;

    bool setData(const QByteArray &datagram, QHostAddress &senderAddress, HostPort &senderPort);
};

#endif // REQUEST_H
