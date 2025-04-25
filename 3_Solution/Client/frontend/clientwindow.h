#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>

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

    void on_searchButton_clicked();

    // Sloturile pentru scrollare
    void scrollUp();
    void scrollDown();


    void on_searchBar_returnPressed();

    void on_searchBar_textChanged(const QString &arg1);

    void on_searchBar_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::clientWindow *ui;
    QString username;
    QScrollArea *scrollArea;        // ScrollArea principală
    QWidget *contentWidget;         // Widget-ul care conține elementele din scrollArea
    QVBoxLayout *contentLayout;     // Layout pentru widget-ul din scrollArea
};

#endif // CLIENTWINDOW_H
