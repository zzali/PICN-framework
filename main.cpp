#include <QApplication>
#include <QNetworkProxy>
//#include <MainWidget.h>
#include <QProcess>
#include <iostream>
#include <string>
#include "ProxyServer.h"
#include "RepositoryCreatorThread.h"
#include "PublisherServer.h"
#include "LocalNeighborFinderThread.h"
#include "SendHelloThread.h"
#include "RegisterRepository.h"
#include "LogThread.h"

//#include "webproxy.h"


//zz{
LogThread *debugThread;

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    debugThread->addLog(msg);
}


//zz}

int main(int argc, char *argv[])
{
    QApplication *a;
    RepositoryCreatorThread *t;
    SendHelloThread *h;
    ProxyServer *server;
    
//    QNetworkProxy prx(QNetworkProxy::Socks5Proxy, "127.0.0.1", 9050);
//    QNetworkProxy::setApplicationProxy(prx);


    while(1) {
        try{
            a = new QApplication(argc, argv);
//            MainWidget *w = new MainWidget();
//            w->show();
            //zz{
            //get seeker IP
            qDebug() <<"PICN Client: Please Enter the seeker IP (Ex. 192.168.2.150):";
            QTextStream qin(stdin);
            Definitions::setSeekerIP(qin.readLine());

            debugThread = new LogThread();
            debugThread->start();
            qInstallMessageHandler(customMessageHandler);


            //zz}
            t = new RepositoryCreatorThread();
            t->start();
            //zz{
            h = new SendHelloThread();
            h->start();
            //zz}
//            std::cout << "Enter your LAN address: (e.g. 192.168.1)\n";
//            std::string s;
//            std::cin >> s;
//            s = "192.168.1";
//            LocalNeighborFinderThread *l =
//                    new LocalNeighborFinderThread(QString::fromStdString(s));
//            l->start();

            server = new ProxyServer();

            PublisherServer *publisherServer = new PublisherServer();


            //QString program = "./OperaPortable/OperaPortable";
            //QStringList arguments;
            //QProcess *myProcess = new QProcess();
            //myProcess->start(program, arguments);

            a->exec();
        }
        catch(...) {
            qDebug() << "An Exception occured...";
        }
    }
}
