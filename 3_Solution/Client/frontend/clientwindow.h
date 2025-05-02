#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "accommodation.h"
#include<QLabel>

namespace Ui {
class clientWindow;
}

class clientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientWindow(QWidget *parent = nullptr,QString username="");
    ~clientWindow();
   // void showAccommodations();
   // void showAttractions();
   // void showTransportations();
    void designScroller(QScrollArea* scroller);
    void populateAccColumn(QWidget* widget);
    void loadDataFromServer();
    void formatLabel(QLabel *label, Accommodation *acc, Destination *dest);

signals:
    void backToLogin();

private slots:
    void on_logout_clicked();

    void on_pushAcc_clicked();

    void on_pushAtt_clicked();

    void on_pushTra_clicked();

private:
    Ui::clientWindow *ui;
    QString username;
    QScrollArea* scrollAcc;
    QScrollArea* scrollAtt;
    QScrollArea* scrollTra;
    QPushButton* butAcc;
    QPushButton* butAtt;
    QPushButton* butTra;
    QWidget* widAcc;
    QWidget* widAtt;
    QWidget* widTra;
    QVector<Accommodation*> accommodations;
    QVector<QPushButton*> accommodationButtons;


};

#endif // CLIENTWINDOW_H
