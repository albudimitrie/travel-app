#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>

namespace Ui {
class clientWindow;
}

class clientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientWindow(QWidget *parent = nullptr,QString username="");
    ~clientWindow();

signals:
    void backToLogin();

private slots:
    void on_logout_clicked();

private:
    Ui::clientWindow *ui;
    QString username;
};

#endif // CLIENTWINDOW_H
