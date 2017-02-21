#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <QObject>
#include <QTcpSocket>
#include <QFileInfo>
#include <QThread>
#include "Definitions.h"
#include "PeerRequest.h"

class Publisher : public QObject
{
    Q_OBJECT
public:
    explicit Publisher(QObject *parent = 0);
    ~Publisher();
    bool deliver(PeerRequest& request);
    bool closeConnection(bool ok);
    void setReceiverSocket(QTcpSocket *peerSocket);
    void waitForBandwidthLimit();
    QTcpSocket *peerSocket;
    QFile *headerFile;
    QFile *contentFile;
    static const int MAX_READ_SIZE = 2000000;//2MB
signals:
    
public slots:
    
};

#endif // PUBLISHER_H
