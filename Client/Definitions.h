#ifndef DEFINITIONS
#define DEFINITIONS

#include <QObject>

typedef qint16 HostPort;
typedef unsigned int ClientID;

class Definitions {
    static Definitions* instance;

public:
    int serverUdpPort = 7070;
    QString seekerIP = "192.168.2.150";
    static Definitions* globalInstance();
    //zz{
    QString logDir = "./Log/";
    int clientRegPort = 8080;
    //zz}
};

#endif // GLOBAL
