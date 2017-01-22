#include "RepositoryCreator.h"

#include <QDebug>
#include <iostream>
#include <QApplication>
RepositoryCreator::RepositoryCreator(QObject *parent) :
    QObject(parent)
{
    f_tmp = new QFile();
    f_header = new QFile();
    f_content = new QFile();
    //qDebug()<<"current directory "<<QApplication::applicationDirPath().toStdString();

    loadInfo();
}

RepositoryCreator::~RepositoryCreator()
{
    delete f_tmp;
    delete f_header;
    delete f_content;
}

void RepositoryCreator::startProcess()
{
    QDir tmp_dir(Definitions::getInstance()->tempDir);
    QStringList nameFilters;
    nameFilters << "*.tmp";

    QFileInfoList tmpList = tmp_dir.entryInfoList(nameFilters);
    for(int i = 0; i < tmpList.size(); i++) {
        processTmpFile(tmpList[i]);
    }
}

void RepositoryCreator::processTmpFile(QFileInfo& fileInfo)
{
    f_tmp->setFileName(fileInfo.filePath());
    f_tmp->open(QIODevice::ReadOnly);
    f_content->setFileName(Definitions::getInstance()->cacheDir + fileInfo.baseName() + ".content");
    f_content->open(QIODevice::WriteOnly);
    f_header->setFileName(Definitions::getInstance()->cacheDir + fileInfo.baseName() + ".header");
    f_header->open(QIODevice::WriteOnly);

    bool first = true;
    while( !f_tmp->atEnd() ) {
        QByteArray data = f_tmp->read(50000);
        if(first) {
            first = false;
            int ind = data.indexOf("\r\n\r\n");
            f_header->write( data.left(ind) );
            f_content->write( data.mid(ind+4) );
        }
        else {
            f_content->write(data);
        }
    }
    f_tmp->remove();

    // !important
    // check to see if the file size is OK!

    f_content->close();

//    QList<QByteArray> hashList;
//    QByteArray hashListMerged;
//    f_content->open(QIODevice::ReadOnly);
//    while(!f_content->atEnd()) {
//        QByteArray data = f_content->read(1024*1024);
//        hashList.append(QCryptographicHash::hash(data, QCryptographicHash::Sha256));
//        hashListMerged.append(data);
//    }
//    f_content->close();

//    QByteArray contentHash = QCryptographicHash::hash(hashListMerged, QCryptographicHash::Sha256);
//    f_header->write(QByteArray("\r\n") + "Cloudy-Digest: " + contentHash.toHex());
//    f_header->write(QByteArray("\r\n") + "Cloudy-Digest-List:");
//    for(int i = 0 ; i < hashList.size(); i++) {
//        f_header->write( " "  + hashList[i].toHex());
//    }
    f_header->write("\r\n\r\n");

    f_header->close();
    ClientCore::getInstance()->setValidOrRemove(fileInfo.baseName(), true);
}


void RepositoryCreator::writeDownInfo()
{
    QFile *file = new QFile(Definitions::getInstance()->configDir + "RepositoryData.data.part");
    file->open(QIODevice::WriteOnly);
    QSet<QString> set;
    //qDebug()<<"Start of writeDownInfo()\n";
    for(int i = 0; i < 3; i++) {
         //for(QMap<QString, bool>::Iterator it = ClientCore::getInstance()->repositoryTable.begin();
        for(QMap<QString, QVector<bool> >::Iterator it = ClientCore::getInstance()->repositoryTable.begin();
            it != ClientCore::getInstance()->repositoryTable.end(); it++) {
            if(it.value()[0] == true) {
                set.insert(it.key());
                //zz{
                //qDebug()<<"RepositoryCreator::writeDownInfo(): "<<(it.key()).toStdString()
                //        << " is saved in file\n";
                //zz}
            }
        }
    }
    for(QSet<QString>::Iterator it = set.begin(); it != set.end(); it++)
        file->write(QString((*it) + "\n").toUtf8());
    file->close();
    QFile::remove(Definitions::getInstance()->configDir + "RepositoryData.data");
    file->rename(Definitions::getInstance()->configDir + "RepositoryData.data");
    delete file;
}

void RepositoryCreator::loadInfo()
{
    QFile *file = new QFile(Definitions::getInstance()->configDir + "RepositoryData.data");
    if(!file->open(QIODevice::ReadOnly))
        return;

    QTextStream in(file);
    QString tmp;
    while(!in.atEnd()) {
        tmp = in.readLine();
        ClientCore::getInstance()->registerInRepository(tmp, true);
    }

    file->close();
}
