#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QLayout>
#include <QString>
#include"Socket.h"
#include<QString>
//#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    layout->addWidget(ui->groupBox, 0, Qt::AlignCenter);
    ui->centralwidget->setLayout(layout);

    ui->groupBox->setMinimumSize(700, 400);  // Setează dimensiunea minimă
    ui->groupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    char* username = new char[ui->lineEdit->text().size()+1];
    char* password = new char[ui->lineEdit_2->text().size()+1];

    strcpy(username,ui->lineEdit->text().toStdString().c_str());
    strcpy(password,ui->lineEdit_2->text().toStdString().c_str());


    Socket* sock = Socket::getInstance();
    strcat(username,"_");
    strcat(username,password);

    sock->sendMessage(username);

    qDebug()<<username<<password;

    delete []username;
    delete []password;
}
