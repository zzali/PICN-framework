#ifndef REQUEST_H
#define REQUEST_H

#include <QHostAddress>
#include <QStringList>
#include <QCryptographicHash>
#include <QNetworkRequest>
#include "Definitions.h"
#include <QTime>

class Request : public QNetworkRequest
{
public:
    enum RequestType{GET, POST};
    Request(QObject *parent = 0);
    bool parseRequest(QByteArray request);
    bool isCacheable();
    bool isFetchable();
    bool isSupported();
    void setSupported();
//    QString dest_address;
//    int dest_port;
//    QByteArray requestText;
    RequestType requestType;
    QByteArray url;
    QString hash;
    QByteArray contentKey;
    QByteArray requestText;
    bool supported;
    //zz{
    QTime requestTime;
    quint64 size;
    //zz}
};

#endif // REQUEST_H