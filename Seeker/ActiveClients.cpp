#include "ActiveClients.h"
#include <iostream>

//zz ActiveClients* ActiveClients::instance = new ActiveClients ;
QHash<ClientID, Client> ActiveClients::clients;
int ActiveClients::n = 0;
void ActiveClients::checkHelloTimeout()
{
   //zz{
    n++;
    try {
        int i = 0;
        //qDebug() <<"check hello timeout function "<<n<<"\n";
        for(QHash<ClientID, Client>::Iterator it = clients.begin(); it != clients.end();i++ ) {
            if( (*it).getHello() == false ){
                if((*it).getpHello() == false){
                    //zz clients.remove((*it).getId());
                    it = clients.erase(it);
                    //qDebug()<<"checkHelloTimeout: clinet failed "<<i<<"\n";
                }
                else{
                    (*it).setpHello(false);
                    it++;
                }
            }
            else{
                //zz{
                /*if ((*it).getRegister()==false)
                    (*it).requestRegister();*/
                (*it).setHello(false);
                it++;
                //qDebug()<<"checkHelloTimeout: clinet ok " <<i<<"\n";
            }
        }
    }
    catch(...) {

    }
    QThread::msleep(6000);
     //zz}
}


ActiveClients::ActiveClients(QObject *parent) : QObject(parent)
//ActiveClients::ActiveClients()
{
    QTimer *timer = new QTimer(this);
    //timer->moveToThread(this->thread());
    connect(timer, SIGNAL(timeout()), this, SLOT(checkHelloTimeout()));
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
    //zz if(clients.contains(clientID) )
    if(clients.contains(clientID) && clients[clientID].getpHello()==true)
        return true;
    else
        return false;
}
 bool ActiveClients::contained(ClientID clientID)
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
        clients[clientID].setpHello(true);
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
     //zz{
     client.setRegister(false);
     //zz}
    clients.insert(client.getId(), client);
}

/*ActiveClients *ActiveClients::getInstance()
{
    return instance;
}
*/
