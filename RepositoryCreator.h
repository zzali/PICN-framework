#ifndef REPOSITORYCREATOR_H
#define REPOSITORYCREATOR_H

#include <QObject>
#include <QDir>
#include <QStringList>
#include <QFileInfoList>
#include <QList>
#include <QSet>
#include <QCryptographicHash>
#include "Definitions.h"

class RepositoryCreator : public QObject
{
    Q_OBJECT
public:
    explicit RepositoryCreator(QObject *parent = 0);
    ~RepositoryCreator();
    void startProcess();
    void processTmpFile(QFileInfo &fileInfo);
    void writeDownInfo();
    void loadInfo();
signals:
    
public slots:
private:
    QFile *f_tmp, *f_header, *f_content;
    
};

#endif // REPOSITORYCREATOR_H
