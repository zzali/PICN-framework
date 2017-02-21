#ifndef PEERREQUEST_H
#define PEERREQUEST_H

#include <QByteArray>
#include <QStringList>
#include "Definitions.h"

class PeerRequest
{
public:
    PeerRequest();
    bool parseRequest(QByteArray &request);
    bool isFetchable();
    QString hash;
};

#endif // PEERREQUEST_H
