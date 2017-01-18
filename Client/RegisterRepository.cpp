//zz{
#include "RegisterRepository.h"
#include <QFile>
#include <QUdpSocket>
#include "Definitions.h"
#include <iostream>



RegisterRepository::RegisterRepository()
{
    sendUnRegistered();
}

void RegisterRepository::sendUnRegistered(){
    QSet<QString> set;

    for(QMap<QString, QVector<bool> >::Iterator it = ClientCore::getInstance()->repositoryTable.begin();
        it != ClientCore::getInstance()->repositoryTable.end(); it++) {
        if (it.value()[0] == true){
            if(it.value()[1] == false) {
                set.insert(it.key());
                it.value()[1] = true;
            }
        }
    }

    QUdpSocket udpSocket;
    QString hash("");
    int i;
    QSet<QString>::Iterator it = set.begin();
    while(it != set.end()){
        hash.clear();
        for(i=0; it!=set.end() && i<10000; i++){
            hash = hash + (*it).mid(0,8);
            //qDebug()<<"Register "<<(*it).mid(0,8)<<"\n";
            it++;
        }
        //if (it==set.end())
           //qDebug()<<"End\n";
        QByteArray cmd = QByteArray("REGISTER")+ Definitions::getInstance()->clientID;
        cmd.append(hash);
        if(udpSocket.writeDatagram(cmd
                            , QHostAddress(Definitions::getInstance()->seekerIP)
                            , Definitions::getInstance()->seekerPort)<0)
            qDebug() << "Error registering in seeker\n";
        //else
        //    qDebug() << "Successfuly registered in seeker\n";

    }

}

RegisterRepository::~RegisterRepository()
{

}

//zz}
