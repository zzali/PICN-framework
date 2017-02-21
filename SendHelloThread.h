//zz{
#ifndef SENDHELLOTHREAD
#define SENDHELLOTHREAD

#include <QThread>

class SendHelloThread : public QThread
{
    Q_OBJECT
public:
    void run();
    explicit SendHelloThread(QObject *parent = 0);
signals:

public slots:


};

#endif // SENDHELLOTHREAD
//zz}
