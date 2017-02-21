#include "Client.h"
#include <QUdpSocket>

Client::Client()
    //zz:hello(true)
    :hello(true),phello(true),isRegister(false)
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

//zz{
bool Client::getpHello() const
{
    return phello;
}

void Client::setpHello(bool value)
{
    phello = value;
}

bool Client::getRegister() const
{
    return isRegister;
}

void Client::setRegister(bool value)
{
    isRegister = value;
}

void Client::requestRegister(){
    QUdpSocket socket;
    socket.writeDatagram(QByteArray("Request Register"),
                         ip, Definitions::globalInstance()->clientRegPort);
    socket.close();
}

//zz}


