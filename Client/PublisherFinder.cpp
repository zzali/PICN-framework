#include "PublisherFinder.h"
#include "ActiveClients.h"

PublisherFinder* PublisherFinder::instance = new PublisherFinder;

PublisherFinder::PublisherFinder(QObject *parent) : QObject(parent)
{
    contentKeyMap = new QHash<ContentKey, QQueue<ClientID> >;
    contentKeySet = new QHash<ContentKey, QSet<ClientID> >;
}

PublisherFinder::~PublisherFinder()
{

}

bool PublisherFinder::registerContent(ContentKey contentKey, ClientID clientID)
{
    /*zzif(contentKeySet->contains(contentKey)) {
        contentKeySet->insert( contentKey, QSet<ClientID>() );
        contentKeyMap->insert( contentKey, QQueue<ClientID>() );
    }*/
    //zz
    //qDebug()<<"Register content "<<contentKey<<"\n";
    if(!(contentKeySet->contains(contentKey))) {
        contentKeySet->insert( contentKey, QSet<ClientID>() );
        contentKeyMap->insert( contentKey, QQueue<ClientID>() );
    }
    //zz}
    if( (*contentKeySet)[contentKey].contains(clientID) )
        return false;
    (*contentKeySet)[contentKey].insert(clientID);
    (*contentKeyMap)[contentKey].push_back(clientID);
    return true;
}

bool PublisherFinder::unregisterContent(ContentKey contentKey, ClientID clientID)
{
    /*zz if(contentKeySet->contains(contentKey))
        return false;
    if( (*contentKeySet)[contentKey].contains(clientID) )
        return false;
        */
    //zz{
    if(!(contentKeySet->contains(contentKey)))
            return false;
    if( !((*contentKeySet)[contentKey].contains(clientID)) )
            return false;
    //zz}
    (*contentKeySet)[contentKey].erase(
                (*contentKeySet)[contentKey].find(clientID) );
    if( (*contentKeySet)[contentKey].size() == 0 ) {
        contentKeySet->erase(contentKeySet->find(contentKey));
        contentKeyMap->erase(contentKeyMap->find(contentKey));
    }
    return true;
}

ClientID PublisherFinder::seekContent(ActiveClients *clients, ContentKey contentKey, bool &ok)
{
    /*zz if( !contentKeyMap->contains(contentKey) ) {

    }*/
    while( contentKeyMap->contains(contentKey) ) {
        ClientID clientID = (*contentKeyMap)[contentKey].front();
        (*contentKeyMap)[contentKey].pop_front();
        if( clients->isActive(clientID) ) {
            ok = true;
            (*contentKeyMap)[contentKey].push_back(clientID);
            //qDebug() <<" find client for content "<<contentKey<<"\n";
            return clientID;
        }
        else {
            unregisterContent(contentKey, clientID);
            qDebug() <<"Not active\n";
        }
    }
    //zz{
    ok = false;
    //qDebug() <<" Not find client for content "<<contentKey<<"\n";
    return NULL;
    //zz}
}

PublisherFinder *PublisherFinder::getInstance()
{
    return instance;
}

