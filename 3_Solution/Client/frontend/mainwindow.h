#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "registerwindow.h"

class clientWindow;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked(); //login

    void on_pushButton_2_clicked(); // Register button

    void on_toolButton_clicked(); //Eye for password

private:
    Ui::MainWindow *ui;
    registerWindow *registerWin = nullptr; // Instance for register window
    bool isPasswordVisible = false;
    clientWindow *clientWin = nullptr;

};
#endif // MAINWINDOW_H
