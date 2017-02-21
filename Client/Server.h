#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>
#include "Definitions.h"



class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject* parent = 0);
    ~Server();
    void initSocket();

private:
    //void processTheDatagram(QByteArray datagram, QHostAddress senderAddress, HostPort senderPort);
    QUdpSocket *udpSocket;

private slots:
    //void readPendingDatagrams();
};

#endif // SERVER_H
