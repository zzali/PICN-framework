#ifndef PROCESSDATAGRAMTHREAD
#define PROCESSDATAGRAMTHREAD



#include <QString>
#include <QThread>
#include <QUdpSocket>
#include <QObject>
#include "Definitions.h"
#include "HelloRequest.h"
#include "RegisterRequest.h"
#include "SeekRequest.h"

class ProcessDatagramThread : public QThread
{
    Q_OBJECT
public:
    explicit ProcessDatagramThread(QObject *parent = 0);
    ~ProcessDatagramThread();
    void run();
    void init(QByteArray datagram, QHostAddress senderAddress, HostPort senderPort);

private:
    QByteArray datagram;
    QHostAddress senderAddress;
    HostPort senderPort;
signals:

public slots:

};

#endif // PROCESSDATAGRAMTHREAD

