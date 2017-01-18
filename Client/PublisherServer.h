#ifndef PUBLISHERSERVER_H
#define PUBLISHERSERVER_H

#include <QObject>
#include <QTcpServer>
#include "PublisherThread.h"
#include "Definitions.h"

class PublisherServer : public QObject
{
    Q_OBJECT
public:
    explicit PublisherServer(QObject *parent = 0);
    QTcpServer *server;
    QTcpSocket *socket;
    int MAX_RESPONSE, responseCount;

signals:
    
public slots:
    void newConnectionArrived();
    void freeMemory();

private:
    PublisherThread *h = NULL;
};

#endif // PUBLISHERSERVER_H
