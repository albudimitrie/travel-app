#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QLayout>
#include <QString>
#include"Socket.h"
#include<QString>
#include <QJsonDocument>
#include <QJsonObject>
#include "registerwindow.h"
#include"factoryrequest.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    layout->addWidget(ui->groupBox, 0, Qt::AlignCenter);
    ui->centralwidget->setLayout(layout);

    ui->groupBox->setMinimumSize(700, 400);  // Set MINIMUM Dimension
    ui->groupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    QPixmap pixmap(":/images/assets/closed.png");
    //qDebug() << "Dimensiunea imaginii:" << pixmap.size();
    if (pixmap.isNull()) {
        qDebug() << "Eroare: Imaginea nu a fost încărcată!";
    } else {
        ui->toolButton->setIcon(QIcon(pixmap));
        ui->toolButton->setIconSize(QSize(24, 24));
        ui->toolButton->setFixedSize(30, 30);
    }
    //ui->toolButton->setAutoRaise(true);
    ui->toolButton->setStyleSheet(
        "QToolButton { background-color: transparent; border: none; }"
        "QToolButton:hover { background-color: rgba(200, 200, 200, 30); }"
        "QToolButton:pressed { background-color: rgba(180, 180, 180, 50); }"
        );
    //ui->toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
}

MainWindow::~MainWindow()
{
    if(registerWin)
    {
        delete registerWin;
    }
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    IRequest *logReq = FactoryRequest::loginReq(ui->lineEdit->text(),ui->lineEdit_2->text());

    Socket* sock = Socket::getInstance();

    qDebug() << logReq->getRequest();

    sock->sendMessage(logReq->getRequest());

    sock->receiveMessage();

}

void MainWindow::on_pushButton_2_clicked()
{
    // If !registerWin -> create registerWin.
    if (!registerWin) {
        registerWin = new registerWindow();
        //Connecting the back signal -> show login window
        connect(registerWin, &registerWindow::backToLogin, this, &MainWindow::show);
    }

    registerWin->show(); // Show register window.
    this->hide();        // Hide current window(login)
}

void MainWindow::on_toolButton_clicked()
{
    isPasswordVisible = !isPasswordVisible;
    QPixmap pixmap(isPasswordVisible ? ":/images/assets/opened.png" : ":/images/assets/closed.png");
    ui->toolButton->setIcon(QIcon(pixmap));
    ui->lineEdit_2->setEchoMode(isPasswordVisible ? QLineEdit::Normal : QLineEdit::Password);
}

