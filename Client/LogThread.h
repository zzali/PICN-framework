#ifndef LOGTHREAD
#define LOGTHREAD
#include <QString>
#include <QFile>
#include <QQueue>
#include <QThread>


class LogThread : public QThread
{
    Q_OBJECT
public:
    explicit LogThread(QObject *parent = 0);
    ~LogThread();
    void run();
    void init();
    void addLog(QString);
private:
    QQueue<QString> *qlog;
    QFile *outFile;
signals:

public slots:

};

#endif // LOGTHREAD

