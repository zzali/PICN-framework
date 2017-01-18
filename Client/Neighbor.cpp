#include "Neighbor.h"

Neighbor::Neighbor()
{
}

Neighbor::Neighbor(QString address, int port)
{
    first = address;
    second = port;
}
