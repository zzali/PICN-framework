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
    //zz{
    bool getpHello() const;
    void setpHello(bool value);
    void requestRegister();
    void setRegister(bool value);
    bool getRegister() const;
    //zz}

    ClientID getId() const;
    void setId(const ClientID &value);

signals:

public slots:

private:
    QHostAddress ip;
    HostPort port;
    bool hello;
    //zz{
    bool phello; //for saving 2 last hello
    bool isRegister;
    //zz}
    ClientID id;
};

#endif // CLIENT_H
