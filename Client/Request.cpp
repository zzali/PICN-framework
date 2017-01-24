#include "Request.h"
#include <iostream>
//#define DBG

Request::Request(QObject *parent)
{
    requestType = GET;
}

bool Request::parseRequest(QByteArray request)
{
    this->requestText = request;
    //zz{
    requestTime = QTime::currentTime();
    //zz}
    int ind = request.indexOf("\r\n\r\n");
    QByteArray header = request.left(ind);
    QByteArray data;
    if(request.size() > ind + 4)
         data = request.mid(ind+4);

    QList<QByteArray> headerList = header.split('\n');
    for(int i = 0; i < headerList.size(); i++)
        headerList[i].remove(headerList[i].size()-1, 1);

    QByteArray first_line = headerList[0];
    if(first_line.split(' ')[0] == "POST")
        requestType = POST;

    this->url = first_line.split(' ')[1].trimmed();
    QByteArray url_for_hash = first_line.split(' ')[1];
    //zz{
    //qDebug()<<"Request::Request: URL: "<<url.toStdString()<<"\n";
    //zz}
    this->setUrl(QUrl(url));
//    qDebug() << url;
    for(int i = 1; i < headerList.size(); i++) {
        int ind = headerList[i].indexOf(':');
        this->setRawHeader(headerList[i].left(ind), headerList[i].mid(ind+1));
    }
    setSupported();
    if(isCacheable() || isFetchable()) {
        QByteArray tmp = QCryptographicHash::hash(url_for_hash, QCryptographicHash::Sha256);
        //zz contentKey = tmp.left(8);
        //qDebug()<<"*****Content Key1: "<<tmp.left(8).toStdString()<<"\n";
        contentKey = tmp.toHex().left(8);
        //qDebug()<<"*****Content Key: "<<contentKey.toStdString()<<"\n";
        hash = QString(tmp.toHex());
    }

    return true;
}

bool Request::isCacheable()
{
    if(ClientCore::getInstance()->isInRepository(hash))
        return false;
//    if(recorderState == RECORD)
//        return true;
//    else
        return isSupported();
}

bool Request::isFetchable()
{
    if(ClientCore::getInstance()->isValidInRepository(hash)){
        //zz{
        //qDebug()<<"content is in repository\n";
        //zz}
        return true;
    }
    else
        return isSupported();
//    if(recorderState == PLAY)
//        return true;
//    else
//        return isSupported();
}

bool Request::isSupported()
{
    return supported;
}

void Request::setSupported()
{
    QByteArrayList supportedList;

    supportedList.append(".jpg");
    supportedList.append(".jpeg");
    supportedList.append(".png");
    supportedList.append(".gif");
    supportedList.append(".flv");
//    supportedList.append(".css");
    supportedList.append(".mp3");
    supportedList.append(".mp4");
//    supportedList.append(".js");
    supportedList.append(".swf");
//    supportedList.append(".exe");
//    supportedList.append(".pdf");
    supportedList.append(".non");

    for(int i=0;i<supportedList.size()-1;i++)
        if(url.contains(supportedList.at(i))) {
            supported = true;
            contentType = supportedList.at(i);
            return;
        }
    contentType = supportedList.at(supportedList.size()-1);
    supported = false;
}
