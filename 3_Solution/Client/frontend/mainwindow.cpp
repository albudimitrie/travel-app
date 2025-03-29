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
    QJsonObject jsonObj;
    jsonObj["action"]="LOG_IN";
    jsonObj["username"] = ui->lineEdit->text();
    jsonObj["password"] = ui->lineEdit_2->text();

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    Socket* sock = Socket::getInstance();
    sock->sendMessage(jsonData);

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
