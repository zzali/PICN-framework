#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "ProxyServer.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();
    ProxyServer *server;
    
private slots:
    void on_pushButton_2_toggled(bool checked);

    void on_pushButton_toggled(bool checked);

    void on_pushButton_3_toggled(bool checked);

private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
