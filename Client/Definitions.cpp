#include "Definitions.h"

#include <QObject>

Definitions* Definitions::instance = new Definitions();

Definitions *Definitions::globalInstance()
{
    return instance;
}

