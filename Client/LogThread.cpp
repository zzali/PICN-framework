#include "LogThread.h"
#include "Definitions.h"
#include <iostream>
#include <string>
#include <QTextStream>


LogThread::LogThread(QObject *parent) :
    QThread(parent)
{
    init();
}

LogThread::~LogThread()
{
    if(outFile->isOpen())
        outFile->close();
}

void LogThread::run()
{
    while(true){
        outFile->open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream ts(outFile);
        int len = qlog->size();
        for(int i=0;i<len;i++){
            ts<<qlog->dequeue();
        }
        ts.flush();
        outFile->close();
        this->sleep(10);
    }

}

void LogThread::init()
{
    qlog = new QQueue<QString>();
    outFile= new QFile(Definitions::globalInstance()->logDir + "log.txt");
    outFile->remove();
}

void LogThread::addLog(QString msg){
    qlog->enqueue(msg);
}

