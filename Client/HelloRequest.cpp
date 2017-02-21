#include "HelloRequest.h"
#include <iostream>
 int HelloRequest::i=0;
HelloRequest::HelloRequest()
{

}

HelloRequest::~HelloRequest()
{

}

bool HelloRequest::processRequest(ActiveClients *clients)
{
    i++;
    //zz{
    //qDebug()<<"Hello request recieved "<<i<<"\n";
    //zz}
    //ActiveClients* clients = ActiveClients::getInstance();
    if( !clients->contained( client.getId() ) ){
        //zz{
        client.setHello(true);
        client.setpHello(true);
        qDebug()<<"New Client registered "<<client.getIp()<<"\n";
        //zz}
        clients->registerClient(client);
    }
    else
        clients->saidHello(client.getId());
}

