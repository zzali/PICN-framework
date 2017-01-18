#ifndef PUBLISHERFINDER_H
#define PUBLISHERFINDER_H

#include <QObject>
#include <QHash>
#include <QQueue>
#include <QSet>
#include "ContentKey.h"
#include "Client.h"
#include "ActiveClients.h"

class PublisherFinder : public QObject
{
    Q_OBJECT
public:
    explicit PublisherFinder(QObject *parent = 0);
    ~PublisherFinder();

    bool registerContent(ContentKey contentKey, ClientID clientID);
    bool unregisterContent(ContentKey contentKey, ClientID clientID);
    ClientID seekContent(ActiveClients *, ContentKey contentKey, bool& ok);

    static PublisherFinder* getInstance();

signals:

public slots:

private:
    QHash<ContentKey, QQueue<ClientID> > *contentKeyMap;
    QHash<ContentKey, QSet<ClientID> > *contentKeySet;

    static PublisherFinder* instance;
};

#endif // PUBLISHERFINDER_H
