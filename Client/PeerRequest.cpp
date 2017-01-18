#include "PeerRequest.h"

PeerRequest::PeerRequest()
{
}

bool PeerRequest::parseRequest(QByteArray& request)
{
    try{
        QString first_line = request.split('\n')[0];
        int ind = first_line.indexOf('\r');
        if(ind != -1)
            first_line.remove(ind, 1);
        QString url = first_line.split(" ")[1];
        ind = url.indexOf("/");
        if(ind != -1)
            this->hash = url.mid(ind+1);
        else
            this->hash = url;
    } catch(...) {
        return false;
    }

    return true;
}

bool PeerRequest::isFetchable()
{
    if(ClientCore::getInstance()->isValidInRepository(hash))
        return true;
    else
        return false;
}
