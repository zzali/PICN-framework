#include "MainWidget.h"
#include "ui_MainWidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButton_2_toggled(bool checked)
{
    ui->pushButton_2->setDisabled(1);
    server = new ProxyServer();
}

void MainWidget::on_pushButton_toggled(bool checked)
{
    if(checked == false)
        Definitions::getInstance()->recorderState = Definitions::getInstance()->DISABLE;
    else
        Definitions::getInstance()->recorderState = Definitions::getInstance()->PLAY;
}

void MainWidget::on_pushButton_3_toggled(bool checked)
{
    if(checked == false) {
        Definitions::getInstance()->recorderState = Definitions::getInstance()->DISABLE;
//        echoEnabled = true;
    }
    else {
        Definitions::getInstance()->recorderState = Definitions::getInstance()->RECORD;
//        echoEnabled = false;
    }
}
