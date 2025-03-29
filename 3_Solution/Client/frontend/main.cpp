#include "mainwindow.h"

#include <QApplication>

#include"Socket.h"

int main(int argc, char *argv[])
{
    //Socket* socket = Socket::getInstance();
    //socket->sendMessage("A MERS\n");
    //socket->sendMessage("A MERS2\n");


    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();



}
