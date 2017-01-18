#ifndef CONTENT_H
#define CONTENT_H

#include <QByteArray>
#include <time.h>

class Content
{
public:
    Content();
    QByteArray fullHash;
    time_t  lastUsedTime;
    bool valid;
};

#endif // CONTENT_H
