#ifndef SEEKREQUEST_H
#define SEEKREQUEST_H

#include "Request.h"

class SeekRequest : public Request
{
public:
    SeekRequest();
    ~SeekRequest();

    bool processRequest(ActiveClients *clients);
};

#endif // SEEKREQUEST_H
