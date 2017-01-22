#include "ProcessDatagramThread.h"
#include "Request.h"

ProcessDatagramThread::ProcessDatagramThread(QObject *parent) :
    QThread(parent)
{

}

ProcessDatagramThread::~ProcessDatagramThread(){

}

void ProcessDatagramThread::run()
{
    QByteArray typeField( datagram.left(8) );
    Request *request;
    ActiveClients *clients = new ActiveClients();

    if( typeField == QByteArray("REGISTER") ){
        request = new RegisterRequest();
    }
    else if( typeField == QByteArray("HELLO---") ) {
        request = new HelloRequest();
    }
    else if( typeField == QByteArray("SEEK----") ) {
        request = new SeekRequest();
    }
    else
        return;

    if( !request->setData(datagram, senderAddress, senderPort) )
        return;
    request->processRequest(clients);


}

void ProcessDatagramThread::init(QByteArray datagram,   QHostAddress senderAddress, HostPort senderPort)
{
    this->datagram = datagram;
    this->senderAddress = senderAddress;
    this->senderPort = senderPort;
}
