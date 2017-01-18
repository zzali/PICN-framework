#include <QCoreApplication>
#include <QFile>
#include "Definitions.h"
#include <QDebug>
#include "Server.h"
#include "LogThread.h"

//zz{
LogThread *debugThread;

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    debugThread->addLog(msg);
}


//zz}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //zz{
    debugThread = new LogThread();
    debugThread->start();
    qInstallMessageHandler(customMessageHandler);
    qDebug() <<"Seeker is started...\n";
    //zz}

    Server *s = new Server();

    return a.exec();
}
