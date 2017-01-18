#include "Client.h"

Client::Client()
    :hello(true)
{

}

Client::~Client()
{

}
HostPort Client::getPort() const
{
    return port;
}

void Client::setPort(const HostPort &value)
{
    port = value;
}
ClientID Client::getId() const
{
    return id;
}

void Client::setId(const ClientID &value)
{
    id = value;
}

bool Client::getHello() const
{
    return hello;
}

void Client::setHello(bool value)
{
    hello = value;
}


QHostAddress Client::getIp() const
{
    return ip;
}

void Client::setIp(const QHostAddress &value)
{
    ip = value;
}


