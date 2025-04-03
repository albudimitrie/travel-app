#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>

namespace Ui {
class registerWindow;
}

class registerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit registerWindow(QWidget *parent = nullptr);
    ~registerWindow();

signals:
    void backToLogin(); // Signal to return .

private slots:
    void on_pushButton_clicked(); // Button for SUBMIT .

    void on_pushButton_2_clicked(); // Button for 'go back to login'

    void on_toolButton_clicked(); //EYE Pass

private:
    Ui::registerWindow *ui;
    bool isPasswordVisible = false;
};

#endif // REGISTERWINDOW_H
