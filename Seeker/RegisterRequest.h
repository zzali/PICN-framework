#ifndef REGISTERREQUEST_H
#define REGISTERREQUEST_H

#include "Request.h"

class RegisterRequest: public Request
{
public:
    RegisterRequest();
    ~RegisterRequest();

    bool processRequest(ActiveClients *clients);
};

#endif // REGISTERREQUEST_H
