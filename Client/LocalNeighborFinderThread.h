#ifndef LOCALNEIGHBORFINDERTHREAD_H
#define LOCALNEIGHBORFINDERTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include "Neighbor.h"
//#include "Globals.h"

class LocalNeighborFinderThread : public QThread
{
    Q_OBJECT
public:
    explicit LocalNeighborFinderThread(QString LANAddress, QObject *parent = 0);
    void run();
    QString LANAddress;
signals:

public slots:

};

#endif // LOCALNEIGHBORFINDERTHREAD_H
