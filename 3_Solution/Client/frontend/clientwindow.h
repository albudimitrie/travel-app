#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>
#include "accommodation.h"
#include "attraction.h"
#include <QLabel>
#include "transportationroute.h"
#include <QSpinBox>
#include <QDate>
#include "trip.h"
#include "wallet.h"
#include "walletdialog.h"
#include <QComboBox>

namespace Ui {
class clientWindow;
}

class clientWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientWindow(QWidget *parent = nullptr,QString username="",double balance=0);
    ~clientWindow();
    void designScroller(QScrollArea* scroller);
    void populateAccColumn(QWidget* widget);
    void loadDataFromServer();
    void formatAccLabel(QLabel *label, Accommodation *acc, Destination *dest);
    void populateAttColumn(QWidget* widget);
    void formatAttLabel(QLabel *label, Attraction *att, Destination *dest);
    void populateRouColumn(QWidget* widget);
    void formatRouLabel(QLabel *label, TransportationRoute *route);
    void populateTripColumn(QWidget* widget);
    void formatTripLabel(QLabel *label, Trip *trip);
    void clearHighlightedDates();
    QVector<int> jsonArrayToQVector(const QJsonArray &jsonArray);
    void verify_day();
    void finish_booking();
    void reset_buttons_states(QVector<QPushButton*> buttons);
    void highlightDateRange(QDate start,QDate end);
    void showTripDetails(Trip* trip);
    void showGeneratedTrips(QJsonObject);

    // Pentru afisarea detaliilor zilnice ale calatoriei
    QVector<Accommodation*> getDayAccommodations(Trip* trip, int day);
    QVector<Attraction*> getDayAttractions(Trip* trip, int day);
    QVector<TransportationRoute*> getDayRoutes(Trip* trip, int day);

    QWidget* createAccommodationWidget(Accommodation* acc);
    QWidget* createAttractionWidget(Attraction* att);
    QWidget* createRouteWidget(TransportationRoute* route);

    QString formatDuration(int minutes);

    Accommodation* findAccommodationById(int id);
    Attraction* findAttractionById(int id);
    TransportationRoute* findRouteById(int id);
    Trip* findTripById(int id);
    void clearTripData();

    //generare
    void showGeneratedTripDetails(Trip*trip);
    void clearLayout(QLayout* layout);


    //search


signals:
    void backToLogin();

private slots:
    void on_logout_clicked();

    void on_pushAcc_clicked();

    void on_pushAtt_clicked();

    void on_pushTra_clicked();

    void on_cancelBut_clicked();

    void on_backBut_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_histBut_clicked();

    void on_bookBut_clicked();

    void on_confirmBut_clicked();


    void on_autoBut_clicked();

    void on_autoBackBut_clicked();

    void on_walletBut_clicked();

private:
    Wallet* wallet;

    int zile = 0;
    int ziCurenta = 0;
    QDate startDate;
    QDate endDate;
    bool isFirstClick = true;
    bool canBook = false;

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

    QPushButton *walletBut;
    QVector<Accommodation*> accommodations;
    QVector<QPushButton*> accommodationButtons;
    QVector<Attraction*> attractions;
    QVector<QPushButton*>attractionButtons;
    QVector<TransportationRoute*>routes;
    QVector<QPushButton*>routesButtons;
    QHash<int, Transportation*> transportationCache;


//PARTICULAR BOOK
    QLabel *showPeriod;
    QLabel *questionLabel;
    QSpinBox *daysSpinBox;
    QPushButton *particularButton;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
    QVector<int> idBookedAcc;
    QVector<int> idBookedAtt;
    QVector<int> idBookedRou;

//HISTORY
    QLabel *historyLabel;
    QPushButton* historyButton;
    QVector<Trip*> trips;
    QPushButton* backButton;
    QScrollArea* scrollTrips;
    QWidget* widTrips;
    QVector<QPushButton*>tripButtons;

//AUTOMATIC BOOK

    QLabel *automaticLabel;
    QPushButton* autoButton;
    QPushButton* autoBackButton;
    QVector<Trip*>tripsGenerated;
    QWidget* mainWidget=nullptr;


    QMap<int, QLabel*> tripLabels;//unused at this moment
    QMap<int, QLabel*> accLabels;//unused at this moment
    QMap<int, QLabel*> attLabels;//unused at this moment
    QMap<int, QLabel*> traLabels;

    // search components
    QLineEdit* searchAccEdit;
    QLineEdit* searchAttEdit;
    QLineEdit* searchRouEdit;

    // search functions
    void setupSearch();
    void filterAccommodations(const QString& searchText);
    void filterAttractions(const QString& searchText);
    void filterRoutes(const QString& searchText);
    QPushButton* customActionButton;

};

#endif // CLIENTWINDOW_H
