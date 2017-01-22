#ifndef PROVIDER_H
#define PROVIDER_H

#include <QObject>
#include <Request.h>
#include <QTcpSocket>
#include "Definitions.h"

class Provider : public QObject
{
    Q_OBJECT
public:
    explicit Provider(QObject *parent = 0);
    ~Provider();
    void setPeerAddress(QString address, int port);
    bool failed();
    QString peerAddress;
    int peerPort;
    //zz bool deliver(Request request);
    bool deliver(Request *request, QTcpSocket *clientSocket);
    QTcpSocket *peerSocket;
    QFile *f;
signals:

public slots:

};

#endif // PROVIDER_H
