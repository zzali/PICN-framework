#include "HTTPProvider.h"
#include <iostream>
#include <QTimer>

HTTPProvider::HTTPProvider(QObject *parent) :
    QObject(parent)
{
    file = NULL;
    receiveCount = 0;
}

HTTPProvider::~HTTPProvider()
{
}


void HTTPProvider::startConnection(Request *request)
{
    request->firstByteTime = QTime::currentTime();
    firstReply = true;
    this->request = request;
    //zz{
    this->request->size = 0;

    //zz}
    reply = accessManager->get(*request);

    connect(reply, SIGNAL(readyRead()),
            this, SLOT(readyRead()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(errorOccured(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()),
            this, SLOT(transferFinished()));

    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(checkTimeout()));
    timer->start(2000);
    timeout = false;

    if(request->isCacheable()) {
//        qDebug() << request->url << endl;
        ClientCore::getInstance()->registerInRepository(request->hash);
        file = new QFile(Definitions::getInstance()->tempDir + request->hash + ".tmp.part");
        if(!file->open(QIODevice::WriteOnly)) {
            delete file;
            file = NULL;
        }
    }


}


void HTTPProvider::setReceiverSocket(QTcpSocket *clientSocket, QNetworkAccessManager *accessManager)
{
    this->clientSocket = clientSocket;
    this->accessManager = accessManager;
}

bool HTTPProvider::readyRead()
{

    if(clientSocket->state() == QTcpSocket::UnconnectedState) {
        errorOccured(QNetworkReply::ProtocolUnknownError);
        //zz{
        //qDebug()<<"errorOccured in clientSocket start of HTTPProvider::readyRead\n";
        //zz}
        return false;
    }
    if(firstReply) {
        firstReply = false;

        //zz{
        //qDebug()<<"firstReply if in HTTPProvider::readyRead before writeReplyHeader\n";
        //zz}
        writeReplyHeader();
    }


    //zz{
    request->size += reply->bytesAvailable();
    //qDebug() <<"request->size is "<<request->size<<"\n";
    //zz}
    QByteArray data = reply->readAll();

    /*zzif(file != NULL && file->isOpen()) {
        file->write(data);
        file->flush();
    }

    clientSocket->write(data);
    clientSocket->flush();*/
    request->dataReply.append(data);
    //zz{

    //qDebug()<<"HTTPProvider::readyRead:end of method after clientSocket.flush\n";
    //zz}
    timeout = false;
    return true;
}

void HTTPProvider::errorOccured(QNetworkReply::NetworkError err)
{
    if(firstReply) {
        firstReply = false;
        writeReplyHeader();
    }
    //zz{
    if (!request->dataReply.isEmpty()){
        if(file != NULL && file->isOpen()) {
            file->write(request->dataReply);
            file->flush();
        }

        clientSocket->write(request->dataReply);
        clientSocket->flush();
     }
    //zz}
    if(file != NULL) {
        file->remove();
        delete file;
        file = NULL;
    }
//    qDebug() << "An Error Occured! ......." << (int)err << " First: " << firstReply;
    endOfThread();
}

void HTTPProvider::transferFinished()
{
    if(firstReply) {
        firstReply = false;
        writeReplyHeader();
    }
    if (!request->dataReply.isEmpty()){
        if(file != NULL && file->isOpen()) {
            file->write(request->dataReply);
            file->flush();
        }

        clientSocket->write(request->dataReply);
        clientSocket->flush();
     }

//    QByteArray data;
//    data.append(reply->readAll());

//    if(data.size() != 0 &&
//            clientSocket->state() == QTcpSocket::ConnectedState) {
//        clientSocket->write(data);
//        clientSocket->flush();
//        if(file != NULL && file->isOpen()) {
//            file->write(data);
//            file->flush();
//        }
//    }

    if(file != NULL) {
        if(file->isOpen())
            file->close();
        file->rename(Definitions::getInstance()->tempDir + request->hash + ".tmp");
        delete file;
        file = NULL;
    }
    //zz{

    qDebug().noquote().nospace()<< qSetFieldWidth(10) << left << "HTTP"<< request->requestTime.msecsSinceStartOfDay()
                       << request->requestTime.msecsTo(request->firstByteTime)<< request->contentType<< request->contentKey
                       <<request->size<<request->requestTime.msecsTo(QTime::currentTime())<<qSetFieldWidth(0)<<"\n";
    //zz}
    endOfThread();
}

void HTTPProvider::endOfThread()
{
    disconnectFromBrowser();
    this->thread()->quit();
}

void HTTPProvider::disconnectFromBrowser()
{
    if(clientSocket != NULL) {
        if(clientSocket->isOpen())
            clientSocket->close();
        clientSocket->disconnectFromHost();
        delete clientSocket;
        clientSocket = NULL;
    }
    if(accessManager != NULL) {
        delete accessManager;
        accessManager = NULL;
    }
}

void HTTPProvider:: writeReplyHeader()
{
    QList<QNetworkReply::RawHeaderPair> header = reply->rawHeaderPairs();
    QByteArray data;
    data.append("HTTP/1.0");
    for(int i = 0; i < 3; i++) {
        //zz{
        /*if(reply->attribute((QNetworkRequest::Attribute)i).isNull())
            qDebug()<<"HTTPProvider::writeReplyHeader: null attribute: "<<
                      reply->attribute((QNetworkRequest::Attribute)i).isValid();*/
        //zz}
        if(reply->attribute((QNetworkRequest::Attribute)i).isValid()) {
            data.append(" ");
            data.append(reply->attribute((QNetworkRequest::Attribute)i).toByteArray());
        }
    }
    data.append("\r\n");
    for(int i = 0; i < header.size(); i++)
        data.append(header[i].first + ":" + header[i].second + " \r\n");
    data.append("\r\n");

    if(file != NULL && file->isOpen()) {
        file->write(data);
        file->flush();
    }

    clientSocket->write(data);
    request->size += data.size();
    clientSocket->flush();
    //zz{
    //qDebug()<<"HTTPProvider::writeReplyHeader end of  writeReplyHeader()\n";
    //zz}
}

void HTTPProvider::checkTimeout()
{
    if(timeout == false)
        timeout = true;
    else {
        errorOccured(QNetworkReply::TimeoutError);
    }
}

//void HTTPProvider::startConnectionV2(Request &request)
//{
////    QString peerAddress(request.url);
////    peerAddress.remove("http://", Qt::CaseInsensitive);
////    peerAddress = peerAddress.split("/")[0];
////    qDebug() << peerAddress;
//    QString peerAddress =  request.rawHeader("Host").trimmed();
////    if(peerAddress.contains("http")) {
////        peerAddress = peerAddress.left(peerAddress.indexOf("http"));
////    }
//    qDebug() << peerAddress;

//    serverSocket->connectToHost(peerAddress, 80);

//    if(!serverSocket->waitForConnected()) {
//        qDebug() << "Not Connedted!";
//        return;
//    }
//    serverSocket->write(request.requestText);
//    serverSocket->flush();

//    int payloadLength = -1, payloadCount = 0;
//    bool headerFetched = false;
//    QByteArray headerData, contentData;
//    while(serverSocket->waitForReadyRead()
//          && !headerFetched) {
//        headerData += serverSocket->readAll();
//        if(headerData.contains("\r\n\r\n"))
//            headerFetched = true;
//    }
////    qDebug() << headerData;
//    contentData = headerData.mid(headerData.indexOf("\r\n\r\n") + 4);
//    headerData = headerData.left(headerData.indexOf("\r\n\r\n"));

//    QList<QByteArray> headerList = headerData.split('\n');
//    bool ok = false;
//    for(int i = 0; i < headerList.size(); i++) {
//        if( headerList[i].toLower().contains("content-length") ) {
//            QByteArray tmp = headerList[i].split(':')[1];
//            tmp = tmp.trimmed();
//            payloadLength = tmp.toInt(&ok);
//        }
//    }
//    if(!ok) {
//        qDebug() << "Content-Length field not found!";
//        qDebug() << headerData;
//        payloadLength = 1000000000;
//    }
//    clientSocket->write(headerData + "\r\n\r\n" + contentData);
//    clientSocket->flush();
//    payloadCount = contentData.length();
//    while(payloadCount < payloadLength &&
//          serverSocket->waitForReadyRead(30000)) {
//        contentData = serverSocket->readAll();
//        payloadCount += contentData.length();
//        clientSocket->write(contentData);
//        clientSocket->flush();
//    }
//    qDebug() << payloadCount << "/" << payloadLength;

////    this->thread()->msleep(100);
//    clientSocket->close();
//    clientSocket->disconnectFromHost();
//}
