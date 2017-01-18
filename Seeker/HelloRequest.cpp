#include "HelloRequest.h"
#include <iostream>
HelloRequest::HelloRequest()
{

}

HelloRequest::~HelloRequest()
{

}

bool HelloRequest::processRequest(ActiveClients *clients)
{
    //zz{
    //qDebug()<<"Hello request recieved\n";
    //zz}
    //ActiveClients* clients = ActiveClients::getInstance();
    if( !clients->isActive( client.getId() ) )
        clients->registerClient(client);
    else
        clients->saidHello(client.getId());
}

