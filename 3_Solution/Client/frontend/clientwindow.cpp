#include "clientwindow.h"
#include "ui_clientwindow.h"
#include"factoryrequest.h"
#include"Socket.h"

clientWindow::clientWindow(QWidget *parent,QString username)
    : QMainWindow(parent)
    , ui(new Ui::clientWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    this->resize(1400, 700); // Dimensiune inițială
    this->setFixedSize(this->size());
    this->username=username;

    ui->label->setText("Logged as : "+username);
    ui->label->setStyleSheet("color: black;");
    ui->label->setVisible(true);
}

clientWindow::~clientWindow()
{
    delete ui;
}

void clientWindow::on_logout_clicked()
{
    IRequest *logoutReq = FactoryRequest::logoutReq(this->username);

    Socket* sock = Socket::getInstance();

    qDebug() << logoutReq->getRequest();

    sock->sendMessage(logoutReq->getRequest());

    sock->receiveMessage();

    this->hide();       // Hide register CLIENT
    emit backToLogin(); // emit the signal to notify the login window to display
\

}

