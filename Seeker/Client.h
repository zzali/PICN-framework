#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QHostAddress>
#include "Definitions.h"

class Client
{
public:
    explicit Client();
    ~Client();  

    QHostAddress getIp() const;
    void setIp(const QHostAddress &value);

    HostPort getPort() const;
    void setPort(const HostPort &value);

    bool getHello() const;
    void setHello(bool value);

    ClientID getId() const;
    void setId(const ClientID &value);

signals:

public slots:

private:
    QHostAddress ip;
    HostPort port;
    bool hello;
    ClientID id;
};

#endif // CLIENT_H
