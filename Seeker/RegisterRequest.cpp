#include "RegisterRequest.h"
#include "PublisherFinder.h"
#include <iostream>

RegisterRequest::RegisterRequest()
{

}

RegisterRequest::~RegisterRequest()
{

}

bool RegisterRequest::processRequest(ActiveClients *clients)
{
    if( payload.size() % 8 != 0 )
        return false;

    for(int i = 0; i < payload.size()/8; i++) {
        ContentKey contentKey( payload.mid(i*8, 8) );
        PublisherFinder::getInstance()->registerContent(contentKey, client.getId());
        //zz{
        qDebug()<<"Register content "<<contentKey<<"\n";
        //zz}
    }

    return true;
}
