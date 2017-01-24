#include "Provider.h"

Provider::Provider(QObject *parent) :
    QObject(parent)
{
    peerSocket = NULL;
    f = NULL;
}

Provider::~Provider()
{
    if(peerSocket != NULL)
        delete peerSocket;
    if(f != NULL) {
        delete f;
    }
}

void Provider::setPeerAddress(QString address, int port)
{
    this->peerAddress = address;
    this->peerPort = port;
}

bool Provider::failed()
{
    f->remove();
    return false;
}

bool Provider::deliver(Request *request, QTcpSocket *clientSocket)
{
    //zz{
    //qDebug() <<"provider: start delivering from publisher\n";
    //zz}
    peerSocket = new QTcpSocket();
    peerSocket->connectToHost(QHostAddress(peerAddress), peerPort);


    f = new QFile(Definitions::getInstance()->tempDir + request->hash + ".tmp.part");
    f->open(QIODevice::WriteOnly);

    if(!peerSocket->waitForConnected(1000)) {
        return false;
    }

    peerSocket->write("GIVE " + request->hash.toUtf8() + "\r\n");
    peerSocket->flush();

    int payloadLength = -1, payloadCount = 0;
    if(peerSocket->waitForReadyRead(3000)) {
        request->firstByteTime = QTime::currentTime();
        QByteArray data = peerSocket->readAll();
        if(data.size() < 9 || data.left(9) == "NOT FOUND") {
            peerSocket->write("END");
            peerSocket->close();
            peerSocket->disconnectFromHost();
            return failed();
        }
        bool ok = false;
        if(!data.contains('\n'))
            return failed();
        QByteArray firstLine = data.split('\n')[0];
        if(!firstLine.contains(' '))
            return failed();
        payloadLength = firstLine.split(' ')[1].toInt(&ok);
        if(!ok) {
            return failed();
        }
        payloadCount += data.size() - firstLine.size() - 1;
        //zz{
        clientSocket->write(data.mid(firstLine.size()+1));
        clientSocket->flush();
        //zz}
        f->write(data.mid(firstLine.size()+1));
    }
    else
        return failed();

    while(payloadCount < payloadLength){
        if(!peerSocket->waitForReadyRead(5000))
            return failed();
        QByteArray data = peerSocket->readAll();
        //zz{
        clientSocket->write(data);
        clientSocket->flush();
        if(clientSocket->state() != QTcpSocket::UnconnectedState)
            clientSocket->waitForBytesWritten(3000);
        //zz}
        f->write(data);
        f->waitForBytesWritten(1000);
        payloadCount += data.size();
    }

    peerSocket->write("END");
    peerSocket->close();
    peerSocket->disconnectFromHost();
    //zz{
    request->size = payloadLength;
    //qDebug() << "Provider payload size for request: "<<request->size<<"\n";
    //zz}
    f->close();
    f->rename(Definitions::getInstance()->tempDir + request->hash + ".tmp");

    return true;
}
