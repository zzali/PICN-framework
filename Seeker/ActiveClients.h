#ifndef ACTIVECLIENTS_H
#define ACTIVECLIENTS_H

#include <QObject>
#include <QHash>
#include <QTimer>
#include <QThread>
#include "Client.h"

class ActiveClients : public QObject
{
    Q_OBJECT

private:
    static QHash<ClientID, Client> clients;
    //QTimer *timer;
    //ActiveClients* instance;
    static int n;

public:
    explicit ActiveClients(QObject *parent = 0);
    //ActiveClients();
    ~ActiveClients();
    bool isActive(ClientID clientID);
    //zz{
    bool contained(ClientID clientID);
    //zz}
    bool saidHello(ClientID clientID);
    Client getClient(ClientID clientID);
    void registerClient(Client client);
    //static void startCheckHello();

    //static ActiveClients* getInstance();


signals:

public slots:

public slots:
    void checkHelloTimeout();
};

#endif // ACTIVECLIENTS_H
