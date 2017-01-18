#ifndef HTTPPROVIDER_H
#define HTTPPROVIDER_H

#include <QObject>
#include <QTcpSocket>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QThread>
#include <QTimer>
#include "Definitions.h"
#include "Request.h"

class HTTPProvider : public QObject
{
    Q_OBJECT
public:
    explicit HTTPProvider(QObject *parent = 0);
    ~HTTPProvider();
    void startConnection(Request &request);
    void setReceiverSocket(QTcpSocket *clientSocket,
                           QNetworkAccessManager *accessManager);
    QTcpSocket *clientSocket;
    QNetworkAccessManager *accessManager;
    QNetworkReply *reply;
    QFile *file;
    Request *request;
    int receiveCount;
    bool firstReply;

    //checking response timeout
    QTimer *timer;
    bool timeout = false;
signals:
    void finished();
    
public slots:
    bool readyRead();
    void errorOccured(QNetworkReply::NetworkError err);
    void transferFinished();
    void endOfThread();
    void disconnectFromBrowser();
    void writeReplyHeader();

    void checkTimeout();
};

#endif // HTTPPROVIDER_H
