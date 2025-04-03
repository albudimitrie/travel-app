#include "mainwindow.h"

#include <QApplication>

#include"Socket.h"

int main(int argc, char *argv[])
{
    Socket* socket = Socket::getInstance();

    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/assets/travel.png"));
    MainWindow w;
    w.show();



    return a.exec();



}
