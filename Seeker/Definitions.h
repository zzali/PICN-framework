#ifndef DEFINITIONS
#define DEFINITIONS

#include <QObject>

typedef qint16 HostPort;
typedef unsigned int ClientID;

class Definitions {
    static Definitions* instance;

public:
    int serverUdpPort = 7070;
    QString seekerIP = "172.17.26.163";
    static Definitions* globalInstance();
    //zz{
    QString logDir = "./Log/";
    //zz}
};

#endif // GLOBAL
