#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QThread>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkAccessManager>
#include "HTTPProvider.h"
#include "sICNProvider.h"
#include "Request.h"

class RequestHandlerThread : public QThread
{
    Q_OBJECT
public:
    explicit RequestHandlerThread(QObject *parent = 0);
    ~RequestHandlerThread();
    void init(QTcpSocket *socket, Request *request);
    void run();
    int id;
    Request *request;
    
signals:
    
public slots:

private:
    QTcpSocket *socket; //*serverSocket;
    QNetworkAccessManager *accessManager;
    HTTPProvider *hProvider;
    sICNProvider *sProvider;
};

#endif // REQUESTHANDLER_H
