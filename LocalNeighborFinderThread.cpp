#include "LocalNeighborFinderThread.h"

LocalNeighborFinderThread::LocalNeighborFinderThread(QString LANAddress, QObject *parent) :
    QThread(parent)
{
    this->LANAddress = LANAddress;
}

void LocalNeighborFinderThread::run()
{
    while(1) {
        qDebug() << "Finding Neighbors...";
        for(int i = 1; i < 255; i++) {
            QTcpSocket socket;
            Neighbor neighbor(LANAddress + "." + QString::number(i)
                              , Definitions::getInstance()->publisherPort);
//            qDebug() << "checking:" << neighbor.first;
            socket.connectToHost(neighbor.first, neighbor.second);
            if(!socket.waitForConnected(200)) {
                ClientCore::getInstance()->removeLocalNeighbor(neighbor);
                continue;
            }
            socket.write("GET NOTHING\r\n");
            if(!socket.waitForReadyRead(200)) {
                ClientCore::getInstance()->removeLocalNeighbor(neighbor);
                continue;
            }
            QByteArray ans = socket.readAll();
            if(ans.left(9) != "NOT FOUND") {
                ClientCore::getInstance()->removeLocalNeighbor(neighbor);
                continue;
            }
            ClientCore::getInstance()->addLocalNeighbor(neighbor);
            qDebug() << "Neighbor:" << neighbor.first;
            socket.close();
        }
//        this->sleep(10);
    }
}
