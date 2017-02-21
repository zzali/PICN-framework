#ifndef NEIGHBOR_H
#define NEIGHBOR_H

#include <QString>
#include <QPair>

class Neighbor : public QPair<QString, int>
{
public:
    Neighbor();
    Neighbor(QString address, int port);

    //int reputation;
    //int account;
};

#endif // NEIGHBOR_H
