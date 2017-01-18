//#ifndef WEBPROXY
//#define WEBPROXY

//#include <QtNetwork>
//class WebProxy: public QObject
//{
//    Q_OBJECT
//public:
//    WebProxy(QObject *parent = 0)
//        : QObject(parent)
//    {
//        QTcpServer *proxyServer = new QTcpServer(this);
//        proxyServer->listen(QHostAddress::Any, 6060);
//        connect(proxyServer, SIGNAL(newConnection()), this, SLOT(manageQuery()));
//        qDebug() << "Proxy server running at port" << proxyServer->serverPort();
//    }
//private slots:
//    void manageQuery() {
//        QTcpServer *proxyServer = qobject_cast<QTcpServer*>(sender());
//        QTcpSocket *socket = proxyServer->nextPendingConnection();
//        connect(socket, SIGNAL(readyRead()), this, SLOT(processQuery()));
//        connect(socket, SIGNAL(disconnected()), socket, SLOT(deleteLater()));
//    }
//    void processQuery() {
//        QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
//        QByteArray requestData = socket->readAll();
//        int pos = requestData.indexOf("\r\n");
//        QByteArray requestLine = requestData.left(pos);
//        requestData.remove(0, pos + 2);
//        QList<QByteArray> entries = requestLine.split(' ');
//        QByteArray method = entries.value(0);
//        QByteArray address = entries.value(1);
//        QByteArray version = entries.value(2);
//        QUrl url = QUrl::fromEncoded(address);
//        if (!url.isValid()) {
//            qWarning() << "Invalid URL:" << url;
//            socket->disconnectFromHost();
//            return;
//        }
//        QString host = url.host();
//        int port = (url.port() < 0) ? 80 : url.port();
//        QByteArray req = url.toEncoded();
//        if (url.hasQuery())
//            req.append('?').append(url.query());
//        requestLine = method + " " + req + " " + version + "\r\n";
//        requestData.prepend(requestLine);
//        QString key = host + ':' + QString::number(port);
//        QTcpSocket *proxySocket = socket->findChild<QTcpSocket*>(key);
//        if (proxySocket) {
//            proxySocket->setObjectName(key);
//            proxySocket->setProperty("url", url);
//            proxySocket->setProperty("requestData", requestData);
//            proxySocket->write(requestData);
//        } else {
//            proxySocket = new QTcpSocket(socket);
//            proxySocket->setObjectName(key);
//            proxySocket->setProperty("url", url);
//            proxySocket->setProperty("requestData", requestData);
//            connect(proxySocket, SIGNAL(connected()), this, SLOT(sendRequest()));
//            connect(proxySocket, SIGNAL(readyRead()), this, SLOT(transferData()));
//            connect(proxySocket, SIGNAL(disconnected()), this, SLOT(closeConnection()));
//            connect(proxySocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(closeConnection()));
//            proxySocket->connectToHost(host, port);
//        }
//    }
//    void sendRequest() {
//        QTcpSocket *proxySocket = qobject_cast<QTcpSocket*>(sender());
//        QByteArray requestData = proxySocket->property("requestData").toByteArray();
//        proxySocket->write(requestData);
//    }
//    void transferData() {
//        QTcpSocket *proxySocket = qobject_cast<QTcpSocket*>(sender());
//        QTcpSocket *socket = qobject_cast<QTcpSocket*>(proxySocket->parent());
//        socket->write(proxySocket->readAll());
//    }
//    void closeConnection() {
//        QTcpSocket *proxySocket = qobject_cast<QTcpSocket*>(sender());
//        if (proxySocket) {
//            QTcpSocket *socket = qobject_cast<QTcpSocket*>(proxySocket->parent());
//            if (socket)
//                socket->disconnectFromHost();
//            if (proxySocket->error() != QTcpSocket::RemoteHostClosedError)
//                qWarning() << "Error for:" << proxySocket->property("url").toUrl()
//                           << proxySocket->errorString();
//            proxySocket->deleteLater();;
//        }
//    }
//};

//#endif // WEBPROXY

