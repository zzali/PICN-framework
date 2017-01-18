#ifndef PUBLISHERTHREAD_H
#define PUBLISHERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "Definitions.h"
#include "Publisher.h"
#include "PeerRequest.h"

class PublisherThread : public QThread
{
    Q_OBJECT
public:
    explicit PublisherThread(QObject *parent = 0);
    ~PublisherThread();
    void run();
    void init(QTcpSocket *socket, int responsePriority);
    int responsePriority;
    QTcpSocket *socket;
    Publisher *publisher;
signals:
    
public slots:
    
};

#endif // PUBLISHERTHREAD_H
