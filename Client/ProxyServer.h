#ifndef PROXYSERVER_H
#define PROXYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <time.h>
#include <QQueue>
#include <QMap>
#include "RequestHandlerThread.h"

class ProxyServer : public QObject
{
    Q_OBJECT
public:
    explicit ProxyServer(QObject *parent = 0);
    ~ProxyServer();
    
signals:
    
public slots:
    void newConnectionArrived();
    void freeMemory();
    void takeFromQueue();
    void takeFromQueue2();
private:
    QTcpServer *server;
    QTimer *timer;
    QTimer *timer2;

    QQueue<RequestHandlerThread*> Q, Q2;
    QList< QQueue<RequestHandlerThread*>* > q;
    QMap<int, int> idMap;
    QList<int> idList;
    int idCount;
    int connectionCounter;
    clock_t lastTime;
};

#endif // PROXYSERVER_H
