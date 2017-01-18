#ifndef REPOSITORYCREATORTHREAD_H
#define REPOSITORYCREATORTHREAD_H

#include <QThread>
#include "RepositoryCreator.h"
#include "RegisterRepository.h"


class RepositoryCreatorThread : public QThread
{
    Q_OBJECT
public:
    explicit RepositoryCreatorThread(QObject *parent = 0);
    void run();
    RepositoryCreator *rc;
    //zz{
    RegisterRepository *RegisterServer;
    //zz}
signals:
    
public slots:
    
};

#endif // REPOSITORYCREATORTHREAD_H
