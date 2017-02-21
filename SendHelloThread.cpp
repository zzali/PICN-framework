//zz{
#include "SendHelloThread.h"
#include <QUdpSocket>
#include"Definitions.h"
#include <iostream>

SendHelloThread::SendHelloThread(QObject *parent) :
    QThread(parent)
{
}

void SendHelloThread::run()
{
    while(1) {
        QUdpSocket udpSocket;
        udpSocket.writeDatagram(QByteArray("HELLO---")
                                + Definitions::getInstance()->clientID
                                , QHostAddress(Definitions::getInstance()->seekerIP)
                                , Definitions::getInstance()->seekerPort);
        this->msleep(6000);
        //zz{
        //qDebug()<<"Hello is sent\n";
        //zz}

    }
}
//zz}
