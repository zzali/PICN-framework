#ifndef CLIENTCORE_H
#define CLIENTCORE_H

#include <QObject>
#include <QMap>
#include <QSet>
#include <QFile>
#include <QVector>
#include "Neighbor.h"

// Singleton

class ClientCore : public QObject
{
    Q_OBJECT
public:

    static ClientCore* getInstance() {return instance;}

    explicit ClientCore(QObject *parent = 0);
    bool isInRepository(QString hash);
    bool isValidInRepository(QString hash);
    bool registerInRepository(QString hash, bool valid = false, bool stag=false);
    bool setValidOrRemove(QString hash, bool valid);
    void addLocalNeighbor(Neighbor neighbor);
    void removeLocalNeighbor(Neighbor neighbor);
    QSet<Neighbor> localNeighbors();
    //zz{
    //QMap<QString, bool> repositoryTable;
    //QVector<bool>: first element is validity, second is a tag representing if this hash is sent to seeker or not
    QMap<QString, QVector<bool> > repositoryTable;
    //zz}
    QSet<Neighbor> neighbors;


signals:

public slots:

private:
    static ClientCore* instance;
};

#endif // CLIENTCORE_H
