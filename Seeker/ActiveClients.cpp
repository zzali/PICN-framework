#include "ActiveClients.h"
#include <iostream>

//ActiveClients* ActiveClients::instance = new ActiveClients;
QHash<ClientID, Client> ActiveClients::clients;
void ActiveClients::checkHelloTimeout()
{
    try {
        for(QHash<ClientID, Client>::Iterator it = clients.begin(); it != clients.end(); ) {
            if( (*it).getHello() == false ){
                clients.remove((*it).getId());
                //zz{
                //qDebug()<<"checkHelloTimeout: clinet failed\n";
                //zz}
            }
            else{
                //zz{
                (*it).setHello(false);
                //qDebug()<<"checkHelloTimeout: clinet ok\n";
                it++;
                //zz}
           }
        }
    }
    catch(...) {

    }
    //QThread::msleep(6000);
}


ActiveClients::ActiveClients(QObject *parent) : QObject(parent)
//ActiveClients::ActiveClients()
{
     timer = new QTimer(this);
    timer->moveToThread(this->thread());
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(checkHelloTimeout()));
    timer->start(6000);
}

ActiveClients::~ActiveClients()
{

}

/*void startCheckHello(){
    this->timer->moveToThread(this->thread());
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(checkHelloTimeout()));
    timer->start(10000);
}*/


 bool ActiveClients::isActive(ClientID clientID)
{
    if(clients.contains(clientID))
        return true;
    else
        return false;
}

bool ActiveClients::saidHello(ClientID clientID)
{
    if( clients.contains(clientID) ) {
        clients[clientID].setHello(true);
        return true;
    }
    else {
        return false;
    }
}

 Client ActiveClients::getClient(ClientID clientID)
{
    if( clients.contains(clientID) )
        return clients[clientID];
    else {
        throw "First call isActive function! (class:ActiveClients, function:getClient)";
    }
}

 void ActiveClients::registerClient(Client client)
{
    clients.insert(client.getId(), client);
}

/*ActiveClients *ActiveClients::getInstance()
{
    return instance;
}
*/
