#include "Publisher.h"

#include <time.h>
clock_t last_time = 0;
int data_size = 0;

Publisher::Publisher(QObject *parent) :
    QObject(parent)
{
    headerFile = NULL;
    contentFile = NULL;
}

Publisher::~Publisher()
{
    if(headerFile != NULL)
        delete headerFile;
    if(contentFile != NULL)
        delete contentFile;
}

bool Publisher::deliver(PeerRequest &request)
{
//    qDebug() << "publisher";
    QString headerFileName = Definitions::getInstance()->cacheDir + request.hash + ".header";
    QString contentFileName = Definitions::getInstance()->cacheDir + request.hash + ".content";
    QFile *headerFile = new QFile(headerFileName);
    QFile *contentFile = new QFile(contentFileName);
    if(!headerFile->open(QIODevice::ReadOnly))
            return closeConnection(false);
    if(!contentFile->open(QIODevice::ReadOnly))
            return closeConnection(false);
    int payloadLength = QFileInfo(headerFileName).size()
            + QFileInfo(contentFileName).size();

    peerSocket->write("TAKE " + QByteArray::number(payloadLength) + " \r\n");
//    qDebug() << "here 16";
    while(!headerFile->atEnd()) {
       // this->waitForBandwidthLimit();
        QByteArray data = headerFile->read(Publisher::MAX_READ_SIZE);
        peerSocket->write(data);
        data_size += data.size();
        //peerSocket->waitForBytesWritten(1000);
        if(!peerSocket->waitForBytesWritten(5000))
            return closeConnection(false);
            //zz return false;
    }
//    qDebug() << "header sent!";
    while(!contentFile->atEnd()) {
       // this->waitForBandwidthLimit();
        QByteArray data = contentFile->read(Publisher::MAX_READ_SIZE);
        peerSocket->write(data);
        data_size += data.size();
        //peerSocket->waitForBytesWritten(1000);
        if(!peerSocket->waitForBytesWritten(5000))
            return closeConnection(false);
            //zzreturn false;
    }
    return closeConnection(true);
}

bool Publisher::closeConnection(bool ok)
{
    if(!ok) {
        //zz peerSocket->write("NOT FOUND");
        //zz peerSocket->flush();
        //zz peerSocket->disconnectFromHost();
        return false;
    }
    else {
        //zzpeerSocket->waitForReadyRead();
        peerSocket->disconnectFromHost();
        return true;
    }
}

void Publisher::setReceiverSocket(QTcpSocket *peerSocket)
{
    this->peerSocket = peerSocket;
}

void Publisher::waitForBandwidthLimit()
{
    this->thread()->msleep(5);
    while( ((double)(clock() - last_time)/(double)CLOCKS_PER_SEC) * 10 < 1
           && data_size > (300000/10) )
        this->thread()->msleep(25);
    if( ((double)(clock() - last_time)/(double)CLOCKS_PER_SEC) * 10 >= 1 ){
        data_size = 0;
        last_time = clock();
    }
}

