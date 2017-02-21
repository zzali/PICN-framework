#ifndef SICNPROVIDER_H
#define SICNPROVIDER_H

#include <QObject>
#include <QFile>
#include <QTcpSocket>
#include <QThread>
#include <QSet>
#include "Provider.h"
#include "Request.h"
#include "Definitions.h"
#include "Neighbor.h"

class sICNProvider : public QObject
{
    Q_OBJECT
public:
    explicit sICNProvider(QObject *parent = 0);
    ~sICNProvider();
    void disconnectFromBrowser();
    void setReceiverSocket(QTcpSocket *clientSocket);
    //zz bool deliver(Request request);
    bool deliver(Request *request);
    //zz bool deliverFromLocalRepository(Request request);
    bool deliverFromLocalRepository(Request *request);

    QTcpSocket *clientSocket;
    QFile *headerFile, *contentFile;
    Provider *provider;
    Request request;
    bool success;
    static const int MAX_READ_SIZE = 100000000;//100MB

signals:

public slots:

};

#endif // SICNPROVIDER_H
