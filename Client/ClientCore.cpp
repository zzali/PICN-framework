#include "ClientCore.h"
#include "Definitions.h"

ClientCore* ClientCore::instance = new ClientCore;

ClientCore::ClientCore(QObject *parent) :
    QObject(parent)
{
    QFile *file = new QFile(Definitions::getInstance()->configDir + "RepositoryData.data");
    if(file->open(QIODevice::ReadOnly)) {
        while(!file->atEnd()) {
            QByteArray ba = file->readLine();
            ba.remove(ba.size()-1, 1);
            setValidOrRemove(ba, true);
        }
    }
    file->close();
    delete file;
}

bool ClientCore::isInRepository(QString hash)
{
    return repositoryTable.contains(hash);
}

bool ClientCore::isValidInRepository(QString hash)
{
    if(repositoryTable.contains(hash))
        return repositoryTable[hash][0];
    else
        return false;
}

bool ClientCore::registerInRepository(QString hash, bool valid, bool stag)
{
    //zz{
    QVector<bool> boolv(2);
    boolv.insert(0,valid);
    boolv.insert(1,stag);
    //zz}
    repositoryTable.insert(hash, boolv);
    return true;
}

bool ClientCore::setValidOrRemove(QString hash, bool valid)
{
    if(valid) {
        if(!repositoryTable.contains(hash))
            registerInRepository(hash);
        repositoryTable[hash][0] = true;
    }
    else {
        if(repositoryTable.contains(hash))
            repositoryTable.remove(hash);
    }
    return true;
}

void ClientCore::addLocalNeighbor(Neighbor neighbor)
{
    neighbors.insert(neighbor);
}

void ClientCore::removeLocalNeighbor(Neighbor neighbor)
{
    if(neighbors.contains(neighbor))
        neighbors.remove(neighbor);
}

QSet<Neighbor> ClientCore::localNeighbors()
{
    return neighbors;
}
