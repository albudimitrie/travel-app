#include "clientwindow.h"
#include "destination.h"
#include "ui_clientwindow.h"
#include "factoryrequest.h"
#include "Socket.h"
#include <QScrollArea>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <stdlib.h>
#include <QJsonArray>
#include <QStyle>
#include <QTimer>
#include <QGraphicsBlurEffect>
#include <QPropertyAnimation>
#include <QTextCharFormat>
#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QComboBox>
#include <QListView>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QFormLayout>
#include <QListWidget>


clientWindow::clientWindow(QWidget *parent,QString username)
    : QMainWindow(parent)
    , ui(new Ui::clientWindow)
{

    this->loadDataFromServer();

    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    this->resize(1400, 700); //Initial sizes
    this->setFixedSize(this->size());
    this->username=username;

    if(username.size()<13)
    {
        ui->label->setText("Logged as : " + username);
    }
    else//daca numele e lung..
    {
        QString usernameLow = username;
        usernameLow[11]='.';
        usernameLow[12]='.';
        ui->label->setText("Logged as: " + usernameLow);
    }

    ui->label->setStyleSheet("color: black;");
    ui->label->setVisible(true);

    ui->label->setStyleSheet(R"(
    QLabel {
        color: #ffffff;
        background: rgba(255, 255, 255, 0.1);
        border-radius: 12px;
        padding: 8px 16px;
        font-weight: 600;
    }
)");

    scrollAcc = ui->scrollAreaAccommodations;
    scrollAtt = ui->scrollAreaAttractions;
    scrollTra = ui->scrollAreaTransportation;
    scrollTrips = ui->scrollAreaTrips;

    widAcc=ui->scrollAreaWidgetContents;
    widAtt=ui->scrollAreaWidgetContents_2;
    widTra=ui->scrollAreaWidgetContents_3;
    widTrips=ui->scrollAreaWidgetContents_4;
    widAcc->setLayout(new QVBoxLayout());
    widAtt->setLayout(new QVBoxLayout());
    widTra->setLayout(new QVBoxLayout());
    widTrips->setLayout(new QVBoxLayout());

    butAcc = ui->pushAcc;
    butAtt = ui->pushAtt;
    butTra = ui->pushTra;

    scrollAcc->hide();
    scrollAtt->hide();
    scrollTra->hide();
    scrollTrips->hide();
    butAcc->hide();
    butAtt->hide();
    butTra->hide();

    designScroller(scrollAcc);
    designScroller(scrollAtt);
    designScroller(scrollTra);
    designScroller(scrollTrips);

    butAcc->setCheckable(true);
    butAtt->setCheckable(true);
    butTra->setCheckable(true);
    butAcc->toggle();

    populateAccColumn(widAcc);
    populateAttColumn(widAtt);
    populateRouColumn(widTra);


    this->cancelButton = ui->cancelBut;
    cancelButton->hide();
    this->questionLabel = new QLabel(this);
    //this->daysSpinBox = new QSpinBox(this);
    this->particularButton = ui->bookBut;
    this->confirmButton= ui->confirmBut;
    confirmButton->hide();

    confirmButton->setCheckable(true);

    questionLabel->setText("Want to book a vacation? Click here ! Select your period from the calendar widget!");
    questionLabel->setStyleSheet(R"(
    color: white;
    font-size: 18px;
    font-weight: bold;
    padding: 8px;
    border: 2px solid white;
    border-radius: 10px;
    background-color: rgba(255, 255, 255, 0.1);  /* un fundal semi-transparent */
)");
    questionLabel->setWordWrap(true);
    questionLabel->resize(320, 120);
    questionLabel->move(330, 15);


    //daysSpinBox->setRange(1, 30);
    //daysSpinBox->move(700, 20);
    //daysSpinBox->resize(100, 30);

    questionLabel->show();
    //daysSpinBox->show();


    this->historyLabel = new QLabel(this);

    historyLabel->setText("Want to see your latest booked trips? Click here!");
    historyLabel->setStyleSheet(R"(
    color: white;
    font-size: 18px;
    font-weight: bold;
    padding: 8px;
    border: 2px solid white;
    border-radius: 10px;
    background-color: rgba(255, 255, 255, 0.1);  /* un fundal semi-transparent */
)");
    historyLabel->setWordWrap(true);
    historyLabel->resize(320, 120);
    historyLabel->move(330, 145);

    this->historyButton=ui->histBut;

    this->backButton=ui->backBut;
    backButton->hide();


    this->automaticLabel = new QLabel(this);
    automaticLabel->setText("Want to generate a random trip? Click here! Select your period from the calendar widget!");
    automaticLabel->setStyleSheet(R"(
    color: white;
    font-size: 18px;
    font-weight: bold;
    padding: 8px;
    border: 2px solid white;
    border-radius: 10px;
    background-color: rgba(255, 255, 255, 0.1);  /* un fundal semi-transparent */
)");
    automaticLabel->setWordWrap(true);
    automaticLabel->resize(320,120);
    automaticLabel->move(330,275);

    this->autoButton = ui->autoBut;
    this->autoBackButton = ui->autoBackBut;
    autoBackButton->hide();



}

clientWindow::~clientWindow()
{
    for (Accommodation* acc : accommodations) {
        if (acc) {
            delete acc;
        }
    }
    accommodations.clear();
    for (QPushButton* btn : accommodationButtons) {
        if(btn){
            delete btn;
        }
    }
    accommodationButtons.clear();
    for (Attraction* att : attractions) {
        if (att) {
            delete att;
        }
    }
    attractions.clear();
    for (QPushButton* btn : attractionButtons) {
        if(btn){
            delete btn;
        }
    }
    attractionButtons.clear();
    for (TransportationRoute* rou : routes) {
        if (rou) {
            delete rou;
        }
    }
    routes.clear();
    for (QPushButton* btn : routesButtons) {
        if(btn){
            delete btn;
        }
    }
    routesButtons.clear();

    if(scrollAcc && !scrollAcc->parent()) delete scrollAcc;
    if(scrollAtt && !scrollAtt->parent()) delete scrollAtt;
    if(scrollTra && !scrollTra->parent()) delete scrollTra;

    if(butAcc && !butAcc->parent()) delete butAcc;
    if(butAtt && !butAtt->parent()) delete butAtt;
    if(butTra && !butTra->parent()) delete butTra;

    if(widAcc && !widAcc->parent()) delete widAcc;
    if(widAtt && !widAtt->parent()) delete widAtt;
    if(widTra && !widTra->parent()) delete widTra;


    delete ui;
}

void clientWindow::designScroller(QScrollArea* scroller)
{
    scroller->setStyleSheet(R"(
    /* Container scrollarea cu margine gradient și umbrisor */
    QScrollArea {
        background: #1e1e1e;
        border: 3px solid transparent;
        border-radius: 12px;
        padding: 3px;
        /* gradient border via background-clip hack */
        background-image:
            linear-gradient(#1e1e1e, #1e1e1e),
            radial-gradient(circle at top left,  #ff6a00, #ee0979);
        background-origin: border-box;
        background-clip: padding-box, border-box;
    }
    QScrollArea > QWidget {
        background: #2a2a2a;
        border-radius: 9px;
    }

    /* Scrollbar verticala cu margine rotunjita și accent colorat */
    QScrollBar:vertical {
        background: transparent;
        width: 12px;
        margin: 0px;
    }
    QScrollBar::handle:vertical {
        background: qlineargradient(
            x1:0, y1:0, x2:1, y2:1,
            stop:0 #ff6a00, stop:1 #ee0979
        );
        min-height: 40px;
        border-radius: 6px;
        border: 2px solid #1e1e1e;
    }
    QScrollBar::handle:vertical:hover {
        min-height: 50px;
    }
    QScrollBar::handle:vertical:pressed {
        min-height: 45px;
        border-color: #333333;
    }
    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical,
    QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
        background: none;
        height: 0px;
    }

    /* Scrollbar orizontală identica, doar inversiune dimensiuni */
    QScrollBar:horizontal {
        background: transparent;
        height: 12px;
        margin: 0px;
    }
    QScrollBar::handle:horizontal {
        background: qlineargradient(
            x1:0, y1:0, x2:1, y2:1,
            stop:0 #ff6a00, stop:1 #ee0979
        );
        min-width: 40px;
        border-radius: 6px;
        border: 2px solid #1e1e1e;
    }
    QScrollBar::handle:horizontal:hover {
        min-width: 50px;
    }
    QScrollBar::handle:horizontal:pressed {
        min-width: 45px;
        border-color: #333333;
    }
    QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal,
    QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
        background: none;
        width: 0px;
    }
)");
}

void clientWindow::on_logout_clicked()
{

    IRequest *ack = FactoryRequest::ackReq();

    IRequest *logoutReq = FactoryRequest::logoutReq(this->username);

    Socket* sock = Socket::getInstance();

    qDebug() << logoutReq->getRequest();

    sock->sendMessage(logoutReq->getRequest());

    sock->receiveMessage();

    this->hide();       // Hide client window
    emit backToLogin(); // Emit the signal to notify the login window to display
    sock->sendMessage(ack->getRequest());

}

void clientWindow::on_pushAcc_clicked()
{
    bool isOn = butAtt->isChecked();
    if(isOn==true)
        butAtt->toggle();

    isOn = butTra->isChecked();
    if(isOn==true)
        butTra->toggle();

    scrollAtt->hide();
    scrollTra->hide();
    scrollAcc->show();
}

void clientWindow::on_pushAtt_clicked()
{
    bool isOn = butAcc->isChecked();
    if(isOn==true)
        butAcc->toggle();

    isOn = butTra->isChecked();
    if(isOn==true)
        butTra->toggle();

    scrollAtt->show();
    scrollTra->hide();
    scrollAcc->hide();
}

void clientWindow::on_pushTra_clicked()
{
    bool isOn = butAcc->isChecked();
    if(isOn==true)
        butAcc->toggle();

    isOn = butAtt->isChecked();
    if(isOn==true)
        butAtt->toggle();

    scrollAtt->hide();
    scrollTra->show();
    scrollAcc->hide();
}

void clientWindow::populateAccColumn(QWidget* widget)
{
    for(int i=0;i<accommodations.size();i++)

    {

        QHBoxLayout* hLayout = new QHBoxLayout();

        QVBoxLayout* vLayout = qobject_cast<QVBoxLayout*>(widget->layout());

        if (vLayout) {

            vLayout->addLayout(hLayout);

        }

        QLabel* label = new QLabel();

        hLayout->addWidget(label);

        Destination * dest = accommodations[i]->destination();

        this->formatAccLabel(label,accommodations[i],dest);

        //label->setAlignment(Qt::AlignCenter);

        label->setStyleSheet(R"(
    QLabel {
        color: #ffffff;
        background: rgba(255, 255, 255, 0.1);
        border-radius: 15px;
        padding: 8px 16px;
        font-weight: 600;

    }
)");

        label->setFixedSize(650, 300);

        QPushButton* button1 = new QPushButton();

        hLayout->addWidget(button1);

        button1->setFixedSize(350,300);

        QString base64Data = accommodations[i]->base64Photo();

        QByteArray byteArray = base64Data.toUtf8();

        QByteArray imageData = QByteArray::fromBase64(byteArray);

        QPixmap pixmap;
        pixmap.loadFromData(imageData);

        QIcon icon(pixmap.scaled(button1->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        button1->setIcon(icon);
        button1->setIconSize(button1->size());
        button1->setCursor(Qt::PointingHandCursor);

        button1->setStyleSheet(R"(
QPushButton {
    background: #2e2e2e;
    border-radius: 15px;
    border: none;
    padding: 0px;
}
)");
        accommodationButtons.push_back(button1);

        button1->setIconSize(button1->size() - QSize(13, 13));

        button1->setProperty("selected", false);


        connect(button1, &QPushButton::clicked, this, [=]() {
            bool isSelected = button1->property("selected").toBool();
            isSelected = !isSelected;
            button1->setProperty("selected", isSelected);

            if (isSelected) {
                button1->setStyleSheet(R"(
            QPushButton {
                background: #2e2e2e;
                border-radius: 15px;
                border: 8px solid green;
                padding: 0px;
            }
        )");
                idBookedAcc.push_back(accommodations[i]->id());
            }
            else {
                button1->setStyleSheet(R"(
            QPushButton {
                background: #2e2e2e;
                border-radius: 15px;
                border: none;
                padding: 0px;
            }
        )");
                idBookedAcc.removeOne(accommodations[i]->id());
            }
        });

    }
}

void clientWindow::populateAttColumn(QWidget* widget)
{
    for(int i=0;i<attractions.size();i++)

    {

        QHBoxLayout* hLayout = new QHBoxLayout();

        QVBoxLayout* vLayout = qobject_cast<QVBoxLayout*>(widget->layout());

        if (vLayout) {

            vLayout->addLayout(hLayout);

        }

        QLabel* label = new QLabel();

        hLayout->addWidget(label);

        Destination * dest = attractions[i]->destination();

        this->formatAttLabel(label,attractions[i],dest);

        //label->setAlignment(Qt::AlignCenter);

        label->setStyleSheet(R"(
    QLabel {
        color: #ffffff;
        background: rgba(255, 255, 255, 0.1);
        border-radius: 15px;
        padding: 8px 16px;
        font-weight: 600;

    }
)");

        label->setFixedSize(650, 300);

        QPushButton* button1 = new QPushButton();

        hLayout->addWidget(button1);

        button1->setFixedSize(350,300);

        QString base64Data = attractions[i]->base64Photo();

        QByteArray byteArray = base64Data.toUtf8();

        QByteArray imageData = QByteArray::fromBase64(byteArray);

        QPixmap pixmap;
        pixmap.loadFromData(imageData);

        QIcon icon(pixmap.scaled(button1->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        button1->setIcon(icon);
        button1->setIconSize(button1->size());
        button1->setCursor(Qt::PointingHandCursor);

        button1->setStyleSheet(R"(
QPushButton {
    background: #2e2e2e;
    border-radius: 15px;
    border: none;
    padding: 0px;
}
)");
        attractionButtons.push_back(button1);

        button1->setIconSize(button1->size() - QSize(13, 13));

        button1->setProperty("selected", false);

        connect(button1, &QPushButton::clicked, this, [=]() {
            bool isSelected = button1->property("selected").toBool();
            isSelected = !isSelected;
            button1->setProperty("selected", isSelected);

            if (isSelected) {
                button1->setStyleSheet(R"(
            QPushButton {
                background: #2e2e2e;
                border-radius: 15px;
                border: 8px solid green;
                padding: 0px;
            }
        )");
                idBookedAtt.push_back(attractions[i]->id());
            }
            else {
                button1->setStyleSheet(R"(
            QPushButton {
                background: #2e2e2e;
                border-radius: 15px;
                border: none;
                padding: 0px;
            }
        )");
                idBookedAtt.removeOne(attractions[i]->id());
            }
        });

    }
}

void clientWindow::populateRouColumn(QWidget* widget)
{
    for(int i=0;i<routes.size();i++)

    {

        QHBoxLayout* hLayout = new QHBoxLayout();

        QVBoxLayout* vLayout = qobject_cast<QVBoxLayout*>(widget->layout());

        if (vLayout) {

            vLayout->addLayout(hLayout);

        }

        QLabel* label = new QLabel();

        hLayout->addWidget(label);

        this->formatRouLabel(label,routes[i]);

        //label->setAlignment(Qt::AlignCenter);

        label->setStyleSheet(R"(
    QLabel {
        color: #ffffff;
        background: rgba(255, 255, 255, 0.1);
        border-radius: 15px;
        padding: 8px 16px;
        font-weight: 600;

    }
)");

        label->setFixedSize(650, 300);

        QPushButton* button1 = new QPushButton();

        hLayout->addWidget(button1);

        button1->setFixedSize(350,300);

        QString base64Data = routes[i]->getTransport()->base64Photo();

        QByteArray byteArray = base64Data.toUtf8();

        QByteArray imageData = QByteArray::fromBase64(byteArray);

        QPixmap pixmap;
        pixmap.loadFromData(imageData);

        QIcon icon(pixmap.scaled(button1->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        button1->setIcon(icon);
        button1->setIconSize(button1->size());
        button1->setCursor(Qt::PointingHandCursor);

        button1->setStyleSheet(R"(
QPushButton {
    background: #2e2e2e;
    border-radius: 15px;
    border: none;
    padding: 0px;
}
)");
        routesButtons.push_back(button1);

        button1->setIconSize(button1->size() - QSize(13, 13));

        button1->setProperty("selected", false);

        connect(button1, &QPushButton::clicked, this, [=]() {
            bool isSelected = button1->property("selected").toBool();
            isSelected = !isSelected;
            button1->setProperty("selected", isSelected);

            if (isSelected) {
                button1->setStyleSheet(R"(
            QPushButton {
                background: #2e2e2e;
                border-radius: 15px;
                border: 8px solid green;
                padding: 0px;
            }
        )");
                idBookedRou.push_back(routes[i]->getId());
            }
            else {
                button1->setStyleSheet(R"(
            QPushButton {
                background: #2e2e2e;
                border-radius: 15px;
                border: none;
                padding: 0px;
            }
        )");
                idBookedRou.removeOne(routes[i]->getId());

            }
        });

    }
}

void clientWindow::loadDataFromServer()
{
    IRequest *ack = FactoryRequest::ackReq();
    //ACCOMMODATIONS LOADING
    IRequest *numberacc = FactoryRequest::numberaccommodationsReq();

    Socket* sock = Socket::getInstance();

    sock->sendMessage(numberacc->getRequest());

    QJsonObject object = sock->receiveMessage();


    int sizeAcc = object["size"].toInt();
     //qDebug() << n;
     QJsonArray values = object["values"].toArray();
     //for(int i=0; i < n ;i++)
     //{
     //   qDebug() << values[i];
     //}
    sock->sendMessage(ack->getRequest());
    for(int i=0;i<sizeAcc;i++)
    {
        IRequest* getAcc = FactoryRequest::accomodationReq(values[i].toInt());

        sock->sendMessage(getAcc->getRequest());

        QJsonObject obj = sock->receiveMessage();

        Destination* dest = new Destination(obj["DestinationID"].toInt(),obj["DestinationName"].toString(),obj["Country"].toString(),
                                            obj["City"].toString(),obj["DestinationDescription"].toString(),obj["Climate"].toString(),
                                            obj["IsActive"].toBool());
        Accommodation* acc = new Accommodation(obj["AccommodationID"].toInt(),obj["Name"].toString(),obj["Type"].toString(),
                                               obj["Address"].toString(),obj["Description"].toString(),obj["PricePerNight"].toInt(),
                                               obj["Facilities"].toString(),dest);


        IRequest* getAccPhoto = FactoryRequest::photoaccomodationReq(values[i].toInt());
        sock->sendMessage(ack->getRequest());
        sock->sendMessage(getAccPhoto->getRequest());
        QJsonObject sizeAccObj = sock->receiveMessage();
        int sizeAccPhoto = sizeAccObj["size"].toInt();

        //qDebug() << size <<"\n";

        QString photo="";
        sock->sendMessage(ack->getRequest());
        QJsonObject photoObj = sock->receiveBigData(sizeAccPhoto);
        photo.append(photoObj["encoded"].toString());

        //qDebug() <<"SIZEUL: "<< photo.size();
        acc->setBase64Data(photo);
        accommodations.push_back(acc);

        sock->sendMessage(ack->getRequest());
    }

    //ATTRACTIONS LOADING
    IRequest* allAttReq = FactoryRequest::allattractionsReq();
    sock->sendMessage(allAttReq->getRequest());

    QJsonObject sizeAttObj = sock->receiveMessage();

    int sizeAtt = sizeAttObj["size"].toInt();

    sock->sendMessage(ack->getRequest());

    QJsonObject attVec = sock->receiveBigData(sizeAtt);

    QJsonArray attractionsArray = attVec["attractions"].toArray();
    sock->sendMessage(ack->getRequest());
    for (const QJsonValue &val : attractionsArray) {
        QJsonObject obj = val.toObject();

        Destination *dest = new Destination(obj["DestinationID"].toInt(),obj["DestinationName"].toString(),obj["Country"].toString(),
                                            obj["City"].toString(),obj["DestinationDescription"].toString(),obj["Climate"].toString(),
                                            obj["IsActive"].toBool());

        Attraction *att = new Attraction(dest,obj["Name"].toString(),obj["Description"].toString(),obj["Category"].toString(),
                                         obj["TicketPrice"].toDouble(),obj["AttractionID"].toInt());


        IRequest* getAttPhoto = FactoryRequest::photoattractionReq(att->id());
        sock->sendMessage(getAttPhoto->getRequest());

        QJsonObject sizeAttObj = sock->receiveMessage();
        int sizeAttPhoto = sizeAttObj["size"].toInt();

        QString photo="";
        sock->sendMessage(ack->getRequest());
        QJsonObject photoObj = sock->receiveBigData(sizeAttPhoto);
        photo.append(photoObj["encoded"].toString());

        //qDebug() <<"SIZEUL: "<< photo.size();
        att->setBase64Photo(photo);

        sock->sendMessage(ack->getRequest());

        attractions.push_back(att);
    }


    //ROUTES LOADING
    IRequest* allRouReq = FactoryRequest::allroutesReq();
    sock->sendMessage(allRouReq->getRequest());

    QJsonObject sizeRouObj = sock->receiveMessage();

    int sizeRou = sizeRouObj["size"].toInt();

    sock->sendMessage(ack->getRequest());

    QJsonObject rouVec = sock->receiveBigData(sizeRou);
    //qDebug() << rouVec;
    QJsonArray routesArray = rouVec["routes"].toArray();
    sock->sendMessage(ack->getRequest());
    for (const QJsonValue &val : routesArray) {
        QJsonObject obj = val.toObject();

        Transportation *tra = new Transportation(obj["TransportationID"].toInt(),obj["Type"].toString(),obj["Company"].toString(),
                                            obj["Description"].toString(),obj["ComfortLevel"].toString(),obj["Capacity"].toInt(),
                                            obj["PricePerKm"].toDouble());

        TransportationRoute* rou = new TransportationRoute(obj["RouteID"].toInt(),obj["CityDeparture"].toString(),obj["CityArrival"].toString(),
                                                           obj["Distance"].toInt(),obj["Duration"].toInt(),tra);


        IRequest* getTraPhoto = FactoryRequest::phototransportationReq(tra->getId());
        sock->sendMessage(getTraPhoto->getRequest());

        QJsonObject sizeTraObj = sock->receiveMessage();
        int sizeTraPhoto = sizeTraObj["size"].toInt();

        QString photo="";
        sock->sendMessage(ack->getRequest());
        QJsonObject photoObj = sock->receiveBigData(sizeTraPhoto);
        photo.append(photoObj["encoded"].toString());

        //qDebug() <<"SIZEUL: "<< photo.size();
        tra->setBase64Photo(photo);

        sock->sendMessage(ack->getRequest());

        routes.push_back(rou);
    }

}

void clientWindow::formatAccLabel(QLabel *label, Accommodation *acc, Destination *dest) {
    QString text;
    text += R"(
        <div style="
            background-color: #2d2d2d;
            color: #e0e0e0;
            padding: 16px;
            border-radius: 6px;
            font-family: 'Segoe UI', Tahoma, Geneva, sans-serif;
            font-size: 10pt;
            line-height: 1.4;
        ">
            <table width="100%" cellspacing="0" cellpadding="0">
                <tr>
                    <td width="49%" style="vertical-align: top; padding-right: 10px; border-left: 3px solid #4CAF50; padding-left: 10px;">
                        <div style='font-weight: bold; color: #4CAF50; margin-bottom: 8px; font-size: 11pt;'>
                            Accommodation Details: )" + acc->name() + R"(
                        </div>
                        <table style='border-spacing: 2px; width: 100%;'>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Type:</td>
                                <td>)" + acc->type() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Address:</td>
                                <td>)" + acc->address() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Description:</td>
                                <td>)" + acc->description() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Price per night:</td>
                                <td><span style='font-weight: bold; color: #4CAF50;'>)" + QString::number(acc->pricePerNight()) + R"( EUR</span></td>
                            </tr>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Facilities:</td>
                                <td>)" + acc->facilities() + R"(</td>
                            </tr>
                        </table>
                    </td>
                    <td width="49%" style="vertical-align: top; padding-left: 10px; border-left: 3px solid #2196F3; padding-left: 10px;">
                        <div style='font-weight: bold; color: #2196F3; margin-bottom: 8px; font-size: 11pt;'>
                            Destination Details: )" + dest->getname() + R"(
                        </div>
                        <table style='border-spacing: 2px; width: 100%;'>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Country:</td>
                                <td>)" + dest->getcountry() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>City:</td>
                                <td>)" + dest->getcity() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Description:</td>
                                <td>)" + dest->getdescription() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Climate:</td>
                                <td>)" + dest->getclimate() + R"(</td>
                            </tr>
                        </table>
                    </td>
                </tr>
            </table>
        </div>
    )";

    label->setText(text);
    label->setTextFormat(Qt::RichText);
    label->setWordWrap(true);
    QFont font("Segoe UI", 9);
    font.setStyleHint(QFont::SansSerif);
    label->setFont(font);
    label->setMargin(0);
}

void clientWindow::formatAttLabel(QLabel *label, Attraction *att, Destination *dest)
{
    QString text;
    text += R"(
        <div style="
            background-color: #2d2d2d;
            color: #e0e0e0;
            padding: 16px;
            border-radius: 6px;
            font-family: 'Segoe UI', Tahoma, Geneva, sans-serif;
            font-size: 10pt;
            line-height: 1.4;
        ">
            <table width="100%" cellspacing="0" cellpadding="0">
                <tr>
                    <td width="49%" style="vertical-align: top; padding-right: 10px; border-left: 3px solid #4CAF50; padding-left: 10px;">
                        <div style='font-weight: bold; color: #4CAF50; margin-bottom: 8px; font-size: 11pt;'>
                            Attraction Details: )" + att->name() + R"(
                        </div>
                        <table style='border-spacing: 2px; width: 100%;'>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Category:</td>
                                <td>)" + att->category() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Description:</td>
                                <td>)" + att->description() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Ticket Price:</td>
                                <td><span style='font-weight: bold; color: #4CAF50;'>)" + QString::number(att->ticketPrice()) + R"( EUR</span></td>
                            </tr>
                        </table>
                    </td>
                    <td width="49%" style="vertical-align: top; padding-left: 10px; border-left: 3px solid #2196F3; padding-left: 10px;">
                        <div style='font-weight: bold; color: #2196F3; margin-bottom: 8px; font-size: 11pt;'>
                            Destination Details: )" + dest->getname() + R"(
                        </div>
                        <table style='border-spacing: 2px; width: 100%;'>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Country:</td>
                                <td>)" + dest->getcountry() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>City:</td>
                                <td>)" + dest->getcity() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Description:</td>
                                <td>)" + dest->getdescription() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 100px; color: #9e9e9e;'>Climate:</td>
                                <td>)" + dest->getclimate() + R"(</td>
                            </tr>
                        </table>
                    </td>
                </tr>
            </table>
        </div>
    )";

    label->setText(text);
    label->setTextFormat(Qt::RichText);
    label->setWordWrap(true);
    QFont font("Segoe UI", 9);
    font.setStyleHint(QFont::SansSerif);
    label->setFont(font);
    label->setMargin(0);
}

void clientWindow::formatRouLabel(QLabel *label, TransportationRoute *route)
{
    QString text;
    Transportation* t = route->getTransport();

    text += R"(
        <div style="background-color: #2d2d2d; color: #e0e0e0; padding: 16px; border-radius: 6px;
                    font-family: 'Segoe UI', Tahoma, Geneva, sans-serif; font-size: 10pt; line-height: 1.4;">
            <table width="100%" cellspacing="0" cellpadding="0">
                <tr>
                    <td width="49%" style="vertical-align: top; padding-right: 10px; border-left: 3px solid #FF9800; padding-left: 10px;">
                        <div style='font-weight: bold; color: #FF9800; margin-bottom: 8px; font-size: 11pt;'>
                            Route Details
                        </div>
                        <table style='border-spacing: 2px; width: 100%;'>
                            <tr><td style='width: 100px; color: #9e9e9e;'>From:</td><td>)" + route->getDeparture() + R"(</td></tr>
                            <tr><td style='color: #9e9e9e;'>To:</td><td>)" + route->getArrival() + R"(</td></tr>
                            <tr><td style='color: #9e9e9e;'>Distance:</td><td>)" + QString::number(route->getDistance()) + R"( km</td></tr>
                            <tr><td style='color: #9e9e9e;'>Duration:</td><td>)" + QString::number(route->getDuration()) + R"( mins</td></tr>
                        </table>
                    </td>
                    <td width="49%" style="vertical-align: top; padding-left: 10px; border-left: 3px solid #3F51B5; padding-left: 10px;">
                        <div style='font-weight: bold; color: #3F51B5; margin-bottom: 8px; font-size: 11pt;'>
                            Transportation Info
                        </div>
                        <table style='border-spacing: 2px; width: 100%;'>
                            <tr><td style='width: 100px; color: #9e9e9e;'>Type:</td><td>)" + t->getType() + R"(</td></tr>
                            <tr><td style='color: #9e9e9e;'>Company:</td><td>)" + t->getCompany() + R"(</td></tr>
                            <tr><td style='color: #9e9e9e;'>Description:</td><td>)" + t->getDescription() + R"(</td></tr>
                            <tr><td style='color: #9e9e9e;'>Comfort:</td><td>)" + t->getComfortLevel() + R"(</td></tr>
                            <tr><td style='color: #9e9e9e;'>Capacity:</td><td>)" + QString::number(t->getCapacity()) + R"(</td></tr>
                            <tr><td style='color: #9e9e9e;'>Avg. Price Per KM:</td><td><span style='font-weight: bold; color: #4CAF50;'>)" + QString::number(t->getAveragePricePerTrip()) + R"( EUR</span></td></tr>
                        </table>
                    </td>
                </tr>
            </table>
        </div>
    )";

    label->setText(text);
    label->setTextFormat(Qt::RichText);
    label->setWordWrap(true);
    QFont font("Segoe UI", 9);
    font.setStyleHint(QFont::SansSerif);
    label->setFont(font);
    label->setMargin(0);
}

void clientWindow::on_bookBut_clicked()
{
    if(canBook)
    {
    scrollAcc->show();
    butAcc->show();
    butAtt->show();
    butTra->show();
    cancelButton->show();
    historyLabel->hide();
    historyButton->hide();
    automaticLabel->hide();
    autoButton->hide();

    if(particularButton)particularButton->hide();
    //if(questionLabel)questionLabel->hide();
    //if(daysSpinBox)daysSpinBox->hide();

    confirmButton->show();

    this->zile = startDate.daysTo(endDate) + 1;

    this->ziCurenta=1;

    questionLabel->setText("ZIUA : " + QString::number(ziCurenta));
    }
    else
    {
        QLabel *labelWarning = new QLabel(this);
        labelWarning->setText("Select the period from the calendar widget!");

        QFont font;
        font.setFamily("Arial");
        font.setPointSize(12);
        font.setBold(true);

        labelWarning->setFont(font);

        labelWarning->setStyleSheet(
            "color: white; "
            "background-color: #FF6347; "
            "border: 1px solid #D32F2F; "
            "border-radius: 5px; "
            "padding: 8px; "
            );

        labelWarning->move(810,60);
        labelWarning->adjustSize();
        labelWarning->setFixedHeight(40);
        labelWarning->show();
        QTimer::singleShot(2000, this, [=]() {
            labelWarning->hide();
            labelWarning->deleteLater();
        });
    }

}

void clientWindow::on_confirmBut_clicked()
{
    this->verify_day();
}

void clientWindow::verify_day()
{
    // Verific daca a selectat la ziua curenta toate cele 3
    if (idBookedAcc.size() == ziCurenta && idBookedAtt.size() == ziCurenta && idBookedRou.size() == ziCurenta)
    {
        ziCurenta++;

        if (ziCurenta > zile)
        {
            scrollAcc->hide();
            scrollAtt->hide();
            scrollTra->hide();
            butAcc->hide();
            butAtt->hide();
            butTra->hide();
            cancelButton->hide();
            historyLabel->show();
            historyButton->show();
            automaticLabel->show();
            autoButton->show();
            questionLabel->setText("Want to book a vacation? Click here ! Select your period from the calendar widget!");
            automaticLabel->setText("Want to generate a random trip? Click here! Select your period from the calendar widget!");
            this->finish_booking();
            confirmButton->hide();
            particularButton->show();
            //daysSpinBox->show();
            return;
        }

        reset_buttons_states(accommodationButtons);
        reset_buttons_states(attractionButtons);
        reset_buttons_states(routesButtons);
        questionLabel->setText("ZIUA : " + QString::number(ziCurenta));
    }
    else
    {
        questionLabel->setText("ZIUA : " + QString::number(ziCurenta) +
                               "\nTrebuie să selectezi câte o opțiune(max) din fiecare categorie.");
    }
}

void clientWindow::finish_booking()
{
    QLabel* bigLabel = new QLabel(this);
    bigLabel->setText("✈️ Planificarea e gata! ✈️");

    QFont font;
    font.setPointSize(36);
    font.setBold(true);
    bigLabel->setFont(font);

    bigLabel->setAlignment(Qt::AlignCenter);
    bigLabel->setGeometry(this->rect());

    bigLabel->setStyleSheet(R"(
    background-color: rgba(0, 0, 0, 180);
    color: white;
    border-radius: 20px;
    padding: 30px;
)");

    bigLabel->show();

    QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(bigLabel);
    bigLabel->setGraphicsEffect(effect);

    QPropertyAnimation* animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(1000);
    animation->setStartValue(1.0);
    animation->setEndValue(0.0);
    animation->setEasingCurve(QEasingCurve::OutQuad);

    connect(animation, &QPropertyAnimation::finished, bigLabel, [=]() {
        bigLabel->hide();
        bigLabel->deleteLater();
    });

    QTimer::singleShot(3000, animation, SLOT(start()));
    // send stage
    // creeaza JSON-ul
    QJsonObject bookingData;

    QJsonArray accArray;
    for (int id : idBookedAcc)
        accArray.append(id);
    bookingData["accommodations"] = accArray;

    QJsonArray attArray;
    for (int id : idBookedAtt)
        attArray.append(id);
    bookingData["attractions"] = attArray;

    QJsonArray rouArray;
    for (int id : idBookedRou)
        rouArray.append(id);
    bookingData["routes"] = rouArray;


    bookingData["duration"] = zile;
    bookingData["starting_date"] = startDate.toString("yyyy-MM-dd");
    bookingData["ending_date"] = endDate.toString("yyyy-MM-dd");
    bookingData["username"] = this->username;
    bookingData["action"]="ADD_CUSTOM_TRIP";
    // Convert to text(for sending)
    QJsonDocument doc(bookingData);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);  // sau .Indented
    const char* jsonCharPtr = jsonData.constData();

    qDebug() << jsonData;

    Socket* sock = Socket::getInstance();
    sock->sendMessage(jsonCharPtr);
    //reset stage

    bool isOn = butAcc->isChecked();
    if(isOn==false)
        butAcc->toggle();

    isOn=butAtt->isChecked();
    if(isOn==true)
        butAtt->toggle();

    isOn=butTra->isChecked();
    if(isOn==true)
        butTra->toggle();


    reset_buttons_states(accommodationButtons);
    reset_buttons_states(attractionButtons);
    reset_buttons_states(routesButtons);

    idBookedAcc.clear();
    idBookedAtt.clear();
    idBookedRou.clear();

    this->clearHighlightedDates();
    canBook=false;
    zile = 0;
    ziCurenta = 0;

}

void clientWindow::reset_buttons_states(QVector<QPushButton*> buttons)
{
    for (auto button : buttons) {
        button->setStyleSheet(R"(
            QPushButton {
                background: #2e2e2e;
                border-radius: 15px;
                border: none;
                padding: 0px;
            }
        )");
        button->setProperty("selected", false);
    }
}

void clientWindow::highlightDateRange(QDate start, QDate end) {
    QTextCharFormat rangeFormat;
    rangeFormat.setBackground(QColor("#FFF59D"));  // galben deschis

    QTextCharFormat edgeFormat;
    edgeFormat.setBackground(QColor("#FF8A65"));  // portocaliu deschis

    QDate d = start;
    while (d <= end) {
        if (d == start || d == end) {
            ui->calendarWidget->setDateTextFormat(d, edgeFormat);
        } else {
            ui->calendarWidget->setDateTextFormat(d, rangeFormat);
        }
        d = d.addDays(1);
    }

    //qDebug() << "Highlighted from" << start.toString() << "to" << end.toString();
}

void clientWindow::on_calendarWidget_clicked(const QDate &date)
{
    if(this->zile != 0)return;
    if (isFirstClick) {
        // Prima selectie — sterge selectia veche (daca exista)
        clearHighlightedDates();

        startDate = date;
        endDate = QDate();  // Reset endDate
        isFirstClick = false;
        //qDebug() << "Start date:" << startDate;
    } else {
        endDate = date;
        isFirstClick = true;
        canBook = true;

        // Corectam daca userul a selectat invers
        if (startDate > endDate)
            std::swap(startDate, endDate);

        int days = startDate.daysTo(endDate) + 1;

        //qDebug() << "Perioada selectata:" << startDate << "pana la" << endDate << "(" << days << "zile)";

        questionLabel->setText(
            "Period: " + startDate.toString("dd.MM.yyyy") + " - " +
            endDate.toString("dd.MM.yyyy") + " (" + QString::number(days) + " days)"
            );
        automaticLabel->setText(
            "Period: " + startDate.toString("dd.MM.yyyy") + " - " +
            endDate.toString("dd.MM.yyyy") + " (" + QString::number(days) + " days)"
            );
        highlightDateRange(startDate, endDate);
    }
}

void clientWindow::clearHighlightedDates(){
    QTextCharFormat defaultFormat;  // Format gol = resetare

    if (startDate.isValid()) {
        ui->calendarWidget->setDateTextFormat(startDate, defaultFormat);
    }
    if (endDate.isValid()) {
        ui->calendarWidget->setDateTextFormat(endDate, defaultFormat);
    }
    if (startDate.isValid() && endDate.isValid()) {
        QDate d = startDate.addDays(1);
        while (d < endDate) {
            ui->calendarWidget->setDateTextFormat(d, defaultFormat);
            d = d.addDays(1);
        }
    }
}

void clientWindow::on_cancelBut_clicked()
{
    //reset stage

    bool isOn = butAcc->isChecked();
    if(isOn==false)
        butAcc->toggle();

    isOn=butAtt->isChecked();
    if(isOn==true)
        butAtt->toggle();

    isOn=butTra->isChecked();
    if(isOn==true)
        butTra->toggle();


    reset_buttons_states(accommodationButtons);
    reset_buttons_states(attractionButtons);
    reset_buttons_states(routesButtons);

    idBookedAcc.clear();
    idBookedAtt.clear();
    idBookedRou.clear();

    this->clearHighlightedDates();
    canBook=false;
    zile = 0;
    ziCurenta = 0;

    scrollAcc->hide();
    scrollAtt->hide();
    scrollTra->hide();
    butAcc->hide();
    butAtt->hide();
    butTra->hide();
    cancelButton->hide();
    historyLabel->show();
    historyButton->show();
    automaticLabel->show();
    autoButton->show();
    questionLabel->setText("Want to book a vacation? Click here ! Select your period from the calendar widget!");
    automaticLabel->setText("Want to generate a random trip? Click here! Select your period from the calendar widget!");
    confirmButton->hide();
    particularButton->show();
    //daysSpinBox->show();

}

QVector<int> clientWindow::jsonArrayToQVector(const QJsonArray &jsonArray) {
    QVector<int> result;
    result.reserve(jsonArray.size());  // Rezervam spatiu pentru eficienta

    for (const QJsonValue &value : jsonArray) {
        result.append(value.toInt());
    }

    return result;
}

void clientWindow::on_histBut_clicked()
{
    questionLabel->hide();
    particularButton->hide();
    historyLabel->move(330, 15);
    historyLabel->setText("YOUR TRIPS (PRESS THE BUTTON TO GO BACK)");
    //historyButton->move(700,60);
    backButton->show();
    historyButton->hide();
    automaticLabel->hide();
    autoButton->hide();


    Socket* sock = Socket::getInstance();

    IRequest *ack = FactoryRequest::ackReq();

    IRequest *tripsReq = FactoryRequest::tripsReq(this->username);

    sock->sendMessage(tripsReq->getRequest());

    QJsonObject objSize = sock->receiveMessage();

    int size = objSize["size"].toInt();

    sock->sendMessage(ack->getRequest());

    QJsonObject objTrips = sock->receiveBigData(size);

    //qDebug()<<objTrips;


    QJsonArray tripsArray = objTrips["trips"].toArray();


    for(int i=0;i<objTrips["number"].toInt();i++)
    {
        QJsonObject tripObj = tripsArray[i].toObject();
        if(findTripById(tripObj["id"].toInt() ) == nullptr)
        {
            Trip* trip = new Trip(jsonArrayToQVector(tripObj["accommodations"].toArray()),jsonArrayToQVector(tripObj["attractions"].toArray()),
                                  jsonArrayToQVector(tripObj["routes"].toArray()),
                                  tripObj["id"].toInt(),tripObj["startingDate"].toString(),tripObj["endingDate"].toString(),
                                  tripObj["duration"].toInt(),tripObj["isConfirmed"].toBool(),tripObj["totalCost"].toDouble());

            trips.push_front(trip);
        }

    }
    sock->sendMessage(ack->getRequest());


    //widTrips->setLayout(new QVBoxLayout);


    this->populateTripColumn(widTrips);
    scrollTrips->show();

}

void clientWindow::clearLayout(QLayout* layout)
{
    if (!layout) return;

    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->setParent(nullptr);
            widget->deleteLater();
        }
        else if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout);
            // NU sterge childLayout pentru ca e detinut probabil de alt widget/layout
            // delete childLayout; // sterge doar daca e un layout creat manual, neatasat
        }
        delete item;  // sterge QLayoutItem-ul luat din layout
    }
}

void clientWindow::on_backBut_clicked()
{
    scrollTrips->hide();
    historyLabel->setText("Want to see your latest booked trips? Click here!");
    historyLabel->move(330, 145);
    questionLabel->show();
    particularButton->show();
    //historyButton->move(700,60);
    backButton->hide();
    historyButton->show();
    automaticLabel->show();
    autoButton->show();

    QLayout* layout = widTrips->layout();
    this->clearLayout(layout);


    for(QPushButton* but : tripButtons) {
        delete but;
    }
    // Golim vectorul
    //trips.clear();
    tripButtons.clear();

}

void clientWindow::populateTripColumn(QWidget* widget)
{
    for (int i = 0; i < trips.size(); ++i)
    {
        QHBoxLayout* hLayout = new QHBoxLayout();
        QVBoxLayout* vLayout = qobject_cast<QVBoxLayout*>(widget->layout());

        if (vLayout) {
            vLayout->addLayout(hLayout);
        }

        QLabel* label = new QLabel();
        hLayout->addWidget(label);

        Trip* trip = trips[i];

        QString labelText = QString(
                                "Trip ID: %1\nStart Date: %2\nEnd Date: %3\nDuration: %4 days\nConfirmed: %5\nTotal Cost: %6 €")
                                .arg(trip->getTripId())
                                .arg(trip->getStartDate())
                                .arg(trip->getEndDate())
                                .arg(trip->getDuration())
                                .arg(trip->getIsConfirmed() ? "Yes" : "No")
                                .arg(trip->getTotalCost());

        label->setText(labelText);

        label->setStyleSheet(R"(
            QLabel {
                color: #ffffff;
                background: rgba(255, 255, 255, 0.1);
                border-radius: 15px;
                padding: 8px 16px;
                font-weight: 600;
            }
        )");

        label->setFixedSize(650, 300);

        this->formatTripLabel(label,trips[i]);

        QPushButton* button1 = new QPushButton("Select Trip");
        hLayout->addWidget(button1);

        button1->setFixedSize(350, 300);

        button1->setCursor(Qt::PointingHandCursor);
        button1->setStyleSheet(R"(
            QPushButton {
                background: #2e2e2e;
                border-radius: 15px;
                border: none;
                padding: 0px;
                color: white;
                font-weight: bold;
            }
        )");

        button1->setProperty("selected", false);
        tripButtons.push_back(button1);

        connect(button1, &QPushButton::clicked, this, [=]() {
            this->showTripDetails(trips[i]);
        });
    }
}

void clientWindow::formatTripLabel(QLabel *label, Trip *trip)
{
    QString text;
    text += R"(
        <div style="
            background-color: #2d2d2d;
            color: #e0e0e0;
            padding: 16px;
            border-radius: 6px;
            font-family: 'Segoe UI', Tahoma, Geneva, sans-serif;
            font-size: 10pt;
            line-height: 1.4;
        ">
            <table width="100%" cellspacing="0" cellpadding="0">
                <tr>
                    <td width="100%" style="vertical-align: top; border-left: 3px solid #FF9800; padding-left: 10px;">
                        <div style='font-weight: bold; color: #FF9800; margin-bottom: 8px; font-size: 11pt;'>
                            Trip Details
                        </div>
                        <table style='border-spacing: 2px; width: 100%;'>
                            <tr>
                                <td style='width: 150px; color: #9e9e9e;'>Start Date:</td>
                                <td>)" + trip->getStartDate() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 150px; color: #9e9e9e;'>End Date:</td>
                                <td>)" + trip->getEndDate() + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 150px; color: #9e9e9e;'>Duration:</td>
                                <td>)" + QString::number(trip->getDuration()) + R"( days</td>
                            </tr>
                            <tr>
                                <td style='width: 150px; color: #9e9e9e;'>Confirmed:</td>
                                <td>)" + (trip->getIsConfirmed() ? "Yes" : "No") + R"(</td>
                            </tr>
                            <tr>
                                <td style='width: 150px; color: #9e9e9e;'>Total Cost:</td>
                                <td><span style='font-weight: bold; color: #4CAF50;'>)" + QString::number(trip->getTotalCost(), 'f', 2) + R"( EUR</span></td>
                            </tr>
                        </table>
                    </td>
                </tr>
            </table>
        </div>
    )";

    label->setText(text);
    label->setTextFormat(Qt::RichText);
    label->setWordWrap(true);

    QFont font("Segoe UI", 9);
    font.setStyleHint(QFont::SansSerif);
    label->setFont(font);
    label->setMargin(0);
}

void clientWindow::showTripDetails(Trip* trip)
{
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Trip Details");
    dialog->resize(900, 700);

    // Layout principal cu scroll
    QVBoxLayout* mainLayout = new QVBoxLayout(dialog);
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* scrollContent = new QWidget();
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);

    // Titlu
    QLabel* titleLabel = new QLabel("<h2 style='color:#4CAF50;'>Trip Details</h2>");
    titleLabel->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(titleLabel);

    // Informatii generale
    QLabel* generalInfo = new QLabel();
    QString infoText;
    infoText += "<b>Trip ID:</b> " + QString::number(trip->getTripId()) + "<br>";
    infoText += "<b>Start Date:</b> " + trip->getStartDate() + "<br>";
    infoText += "<b>End Date:</b> " + trip->getEndDate() + "<br>";
    infoText += "<b>Duration:</b> " + QString::number(trip->getDuration()) + " days<br>";
    infoText += "<b>Confirmed:</b> " + QString(trip->getIsConfirmed() ? "Yes" : "No") + "<br>";
    infoText += "<b>Total Cost:</b> " + QString::number(trip->getTotalCost(), 'f', 2) + " EUR<br><br>";

    // Nr elemente
    infoText += "<b>Accommodations:</b> " + QString::number(trip->getIdAcc().size()) + "<br>";
    infoText += "<b>Attractions:</b> " + QString::number(trip->getIdAtt().size()) + "<br>";
    infoText += "<b>Routes:</b> " + QString::number(trip->getIdRou().size()) + "<br>";
    generalInfo->setText(infoText);
    generalInfo->setStyleSheet("color: #e0e0e0; background-color: #2d2d2d; padding: 12px; border-radius: 8px;");
    generalInfo->setTextFormat(Qt::RichText);
    generalInfo->setWordWrap(true);
    scrollLayout->addWidget(generalInfo);

    // Obtine datele pentru fiecare zi
    QLabel* itineraryTitle = new QLabel("<h3 style='color:#4CAF50;'>Daily Itinerary</h3>");
    itineraryTitle->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(itineraryTitle);

    // Pentru fiecare zi, afisam detaliile
    QDate startDate = QDate::fromString(trip->getStartDate(), "yyyy-MM-dd");

    // Pregatim colectiile de elemente pentru distribuire exacta
    QVector<int> accIds = trip->getIdAcc();
    QVector<int> attIds = trip->getIdAtt();
    QVector<int> routeIds = trip->getIdRou();

    for (int day = 1; day <= trip->getDuration(); ++day) {
        QDate currentDate = startDate.addDays(day - 1);

        // Crearea unui grup expandabil pentru fiecare zi
        QGroupBox* dayGroup = new QGroupBox("Day " + QString::number(day) + " - " + currentDate.toString("dd MMMM yyyy"));
        dayGroup->setStyleSheet("QGroupBox { color: #4CAF50; font-weight: bold; border: 1px solid #3d3d3d; border-radius: 8px; margin-top: 10px; } "
                                "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px; }");
        QVBoxLayout* dayLayout = new QVBoxLayout(dayGroup);

        // CAZARE pentru ziua curenta - exact una per zi
        QLabel* accLabel = new QLabel("<b style='color:#4CAF50;'>Accommodation:</b>");
        dayLayout->addWidget(accLabel);

        if (day <= accIds.size()) {
            Accommodation* acc = findAccommodationById(accIds[day-1]);
            if (acc) {
                QWidget* accWidget = createAccommodationWidget(acc);
                dayLayout->addWidget(accWidget);
            } else {
                QLabel* noAccLabel = new QLabel("Accommodation information not available.");
                noAccLabel->setStyleSheet("color: #a0a0a0; margin-left: 15px;");
                dayLayout->addWidget(noAccLabel);
            }
        } else {
            QLabel* noAccLabel = new QLabel("No accommodation scheduled for this day.");
            noAccLabel->setStyleSheet("color: #a0a0a0; margin-left: 15px;");
            dayLayout->addWidget(noAccLabel);
        }

        // ATRACTIE pentru ziua curenta - exact una per zi
        QLabel* attLabel = new QLabel("<b style='color:#4CAF50;'>Attraction:</b>");
        dayLayout->addWidget(attLabel);

        if (day <= attIds.size()) {
            Attraction* att = findAttractionById(attIds[day-1]);
            if (att) {
                QWidget* attWidget = createAttractionWidget(att);
                dayLayout->addWidget(attWidget);
            } else {
                QLabel* noAttLabel = new QLabel("Attraction information not available.");
                noAttLabel->setStyleSheet("color: #a0a0a0; margin-left: 15px;");
                dayLayout->addWidget(noAttLabel);
            }
        } else {
            QLabel* noAttLabel = new QLabel("No attraction scheduled for this day.");
            noAttLabel->setStyleSheet("color: #a0a0a0; margin-left: 15px;");
            dayLayout->addWidget(noAttLabel);
        }

        // RUTA pentru ziua curenta - exact una per zi
        QLabel* routeLabel = new QLabel("<b style='color:#4CAF50;'>Transportation Route:</b>");
        dayLayout->addWidget(routeLabel);

        if (day <= routeIds.size()) {
            TransportationRoute* route = findRouteById(routeIds[day-1]);
            if (route) {
                QWidget* routeWidget = createRouteWidget(route);
                dayLayout->addWidget(routeWidget);
            } else {
                QLabel* noRouteLabel = new QLabel("Transportation route information not available.");
                noRouteLabel->setStyleSheet("color: #a0a0a0; margin-left: 15px;");
                dayLayout->addWidget(noRouteLabel);
            }
        } else {
            QLabel* noRouteLabel = new QLabel("No transportation route scheduled for this day.");
            noRouteLabel->setStyleSheet("color: #a0a0a0; margin-left: 15px;");
            dayLayout->addWidget(noRouteLabel);
        }

        scrollLayout->addWidget(dayGroup);
    }

    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea);

    // Container pentru butoane
    QWidget* buttonContainer = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonContainer);

    // Buton de confirmare - actualizeaza textul in functie de starea confirmarii
    QPushButton* confirmButton = new QPushButton(trip->getIsConfirmed() ? "Already Confirmed" : "Confirm Trip");
    confirmButton->setFixedSize(140, 40);
    confirmButton->setStyleSheet(R"(
        QPushButton {
            background-color: )" + QString(trip->getIsConfirmed() ? "#808080" : "#2196F3") + R"(;
            color: white;
            border-radius: 8px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: )" + QString(trip->getIsConfirmed() ? "#707070" : "#1976D2") + R"(;
        }
    )");
    buttonLayout->addWidget(confirmButton);

    // Buton de inchidere
    QPushButton* closeButton = new QPushButton("Close");
    closeButton->setFixedSize(120, 40);
    closeButton->setStyleSheet(R"(
        QPushButton {
            background-color: #4CAF50;
            color: white;
            border-radius: 8px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #45A049;
        }
    )");
    buttonLayout->addWidget(closeButton);

    mainLayout->addWidget(buttonContainer, 0, Qt::AlignCenter);

    // Conectarea butonului de inchidere
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);

    // Conectarea butonului de confirmare
    connect(confirmButton, &QPushButton::clicked, [=]() {
        // Verifica daca calatoria este deja confirmata
        if (trip->getIsConfirmed()) {
            QMessageBox::information(dialog, "Already Confirmed",
                                     "This trip is already confirmed!");
            return;
        }

        // intreaba utilizatorul daca doreste sa confirme calatoria
        QMessageBox confirmBox;
        confirmBox.setWindowTitle("Confirm Trip");
        confirmBox.setText("Are you sure you want to confirm this trip?");
        confirmBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        confirmBox.setDefaultButton(QMessageBox::No);
        confirmBox.setIcon(QMessageBox::Question);

        int ret = confirmBox.exec();

        if (ret == QMessageBox::Yes) {
            // Setarea calatoriei ca fiind confirmata
            trip->setIsConfirmed(true);

            //trimitere si la server
            QJsonObject sendConfirmObj;
            sendConfirmObj["action"] = "TRIP_CONFIRM";
            sendConfirmObj["trip_id"] = trip->getTripId();
            //Convert to text(For sending)
            QJsonDocument doc(sendConfirmObj);
            QByteArray jsonData = doc.toJson(QJsonDocument::Compact);  // sau .Indented
            const char* jsonCharPtr = jsonData.constData();

            qDebug() << jsonData;

            Socket* sock = Socket::getInstance();
            sock->sendMessage(jsonCharPtr);

            // Actualizez UI-ul pentru a reflecta noua stare
            QString newInfoText = generalInfo->text();
            newInfoText.replace(
                "<b>Confirmed:</b> No<br>",
                "<b>Confirmed:</b> Yes<br>"
                );
            generalInfo->setText(newInfoText);

            QMessageBox::information(dialog, "Success", "Trip has been confirmed successfully!");
        }
    });

    dialog->exec();
}

QWidget* clientWindow::createAccommodationWidget(Accommodation* acc)
{
    QWidget* widget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(widget);

    // Daca am imagine disponibila
    if (!acc->base64Photo().isEmpty()) {
        QLabel* photoLabel = new QLabel();
        QPixmap pixmap;
        pixmap.loadFromData(QByteArray::fromBase64(acc->base64Photo().toUtf8()));
        photoLabel->setPixmap(pixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        layout->addWidget(photoLabel);
    }

    QVBoxLayout* infoLayout = new QVBoxLayout();
    QLabel* nameLabel = new QLabel("<b>" + acc->name() + "</b>");
    nameLabel->setStyleSheet("color: #e0e0e0; font-size: 14px;");
    infoLayout->addWidget(nameLabel);

    QLabel* typeLabel = new QLabel("Type: " + acc->type());
    typeLabel->setStyleSheet("color: #c0c0c0;");
    infoLayout->addWidget(typeLabel);

    QLabel* priceLabel = new QLabel("Price per night: " + QString::number(acc->pricePerNight()) + " EUR");
    priceLabel->setStyleSheet("color: #c0c0c0;");
    infoLayout->addWidget(priceLabel);

    QLabel* addressLabel = new QLabel("Address: " + acc->address());
    addressLabel->setStyleSheet("color: #c0c0c0;");
    infoLayout->addWidget(addressLabel);

    Destination* dest = acc->destination();
    if (dest) {
        QLabel* destLabel = new QLabel("Location: " + dest->getname());
        destLabel->setStyleSheet("color: #c0c0c0;");
        infoLayout->addWidget(destLabel);
    }

    // Facilities
    if (!acc->facilities().isEmpty()) {
        QLabel* facilitiesLabel = new QLabel("Facilities: " + acc->facilities());
        facilitiesLabel->setStyleSheet("color: #c0c0c0;");
        facilitiesLabel->setWordWrap(true);
        infoLayout->addWidget(facilitiesLabel);
    }

    layout->addLayout(infoLayout);
    widget->setStyleSheet("background-color: #333333; border-radius: 6px; margin: 5px; padding: 8px;");

    return widget;
}

QWidget* clientWindow::createAttractionWidget(Attraction* att)
{
    QWidget* widget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(widget);

    // Daca am imagine disponibila
    if (!att->base64Photo().isEmpty()) {
        QLabel* photoLabel = new QLabel();
        QPixmap pixmap;
        pixmap.loadFromData(QByteArray::fromBase64(att->base64Photo().toUtf8()));
        photoLabel->setPixmap(pixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        layout->addWidget(photoLabel);
    }

    QVBoxLayout* infoLayout = new QVBoxLayout();
    QLabel* nameLabel = new QLabel("<b>" + att->name() + "</b>");
    nameLabel->setStyleSheet("color: #e0e0e0; font-size: 14px;");
    infoLayout->addWidget(nameLabel);

    QLabel* categoryLabel = new QLabel("Category: " + att->category());
    categoryLabel->setStyleSheet("color: #c0c0c0;");
    infoLayout->addWidget(categoryLabel);

    QLabel* priceLabel = new QLabel("Ticket Price: " + QString::number(att->ticketPrice()) + " EUR");
    priceLabel->setStyleSheet("color: #c0c0c0;");
    infoLayout->addWidget(priceLabel);

    Destination* dest = att->destination();
    if (dest) {
        QLabel* destLabel = new QLabel("Location: " + dest->getname());
        destLabel->setStyleSheet("color: #c0c0c0;");
        infoLayout->addWidget(destLabel);
    }

    // Descriere
    if (!att->description().isEmpty()) {
        QLabel* descLabel = new QLabel("Description: " + att->description().left(150) +
                                       (att->description().length() > 150 ? "..." : ""));
        descLabel->setStyleSheet("color: #c0c0c0;");
        descLabel->setWordWrap(true);
        infoLayout->addWidget(descLabel);
    }

    layout->addLayout(infoLayout);
    widget->setStyleSheet("background-color: #333333; border-radius: 6px; margin: 5px; padding: 8px;");

    return widget;
}

QWidget* clientWindow::createRouteWidget(TransportationRoute* route)
{
    QWidget* widget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(widget);

    Transportation* transport = route->getTransport();

    // Adaug imaginea transportului, daca este disponibila
    if (transport && !transport->base64Photo().isEmpty()) {
        QLabel* photoLabel = new QLabel();
        QPixmap pixmap;
        pixmap.loadFromData(QByteArray::fromBase64(transport->base64Photo().toUtf8()));
        photoLabel->setPixmap(pixmap.scaled(400, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        layout->addWidget(photoLabel);
    }

    QVBoxLayout* infoLayout = new QVBoxLayout();

    // Titlul rutei cu origine si destinatie
    QLabel* routeLabel = new QLabel("<b>" + route->getDeparture() + " → " + route->getArrival() + "</b>");
    routeLabel->setStyleSheet("color: #e0e0e0; font-size: 14px;");
    infoLayout->addWidget(routeLabel);

    if (transport) {
        // Numele companiei
        QLabel* companyLabel = new QLabel("Company: " + transport->getCompany());
        companyLabel->setStyleSheet("color: #c0c0c0;");
        infoLayout->addWidget(companyLabel);

        // Tipul transportului
        QLabel* typeInfo = new QLabel("Type: " + transport->getType());
        typeInfo->setStyleSheet("color: #c0c0c0;");
        infoLayout->addWidget(typeInfo);

        // Nivel de confort
        QLabel* comfortLabel = new QLabel("Comfort level: " + transport->getComfortLevel());
        comfortLabel->setStyleSheet("color: #c0c0c0;");
        infoLayout->addWidget(comfortLabel);

        // Pret
        QLabel* priceInfo = new QLabel("Price per KM: " + QString::number(transport->getAveragePricePerTrip()) + " EUR");
        priceInfo->setStyleSheet("color: #c0c0c0;");
        infoLayout->addWidget(priceInfo);
    }

    // Informatii despre ruta
    QHBoxLayout* routeInfoLayout = new QHBoxLayout();

    QLabel* distanceLabel = new QLabel("Distance: " + QString::number(route->getDistance()) + " km");
    distanceLabel->setStyleSheet("color: #c0c0c0;");
    routeInfoLayout->addWidget(distanceLabel);

    // Durata in ore
    int hours = route->getDuration();
    QString durationText;
        durationText = QString("%1h").arg(hours);


    QLabel* durationLabel = new QLabel("Duration: " + durationText);
    durationLabel->setStyleSheet("color: #c0c0c0;");
    routeInfoLayout->addWidget(durationLabel);

    infoLayout->addLayout(routeInfoLayout);

    // Descriere (daca este disponibila)
    if (transport && !transport->getDescription().isEmpty()) {
        QLabel* descLabel = new QLabel("Description: " + transport->getDescription().left(100) +
                                       (transport->getDescription().length() > 100 ? "..." : ""));
        descLabel->setStyleSheet("color: #c0c0c0;");
        descLabel->setWordWrap(true);
        infoLayout->addWidget(descLabel);
    }

    layout->addLayout(infoLayout);
    widget->setStyleSheet("background-color: #333333; border-radius: 6px; margin: 5px; padding: 8px;");

    return widget;
}

Accommodation* clientWindow::findAccommodationById(int id)
{
    // Caut in vectorul de cazari
    for (Accommodation* acc : accommodations) {
        if (acc->id() == id) {
            return acc;
        }
    }
    return nullptr;
}

Attraction* clientWindow::findAttractionById(int id)
{
    // Caut in vectorul de atractii
    for (Attraction* att : attractions) {
        if (att->id() == id) {
            return att;
        }
    }
    return nullptr;
}

TransportationRoute* clientWindow::findRouteById(int id)
{
    // Caut in vectorul de rute
    for (TransportationRoute* route : routes) {
        if (route->getId() == id) {
            return route;
        }
    }
    return nullptr;
}

Trip* clientWindow::findTripById(int id)
{
    for(Trip* trip:trips){
        if(trip->getTripId() == id)
        {
            return trip;
        }
    }
    return nullptr;
}

void clientWindow::showGeneratedTripDetails(Trip* trip)
{
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Trip Details");
    dialog->resize(900, 700);

    // Layout principal cu scroll
    QVBoxLayout* mainLayout = new QVBoxLayout(dialog);
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget* scrollContent = new QWidget();
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);

    // Titlu
    QLabel* titleLabel = new QLabel("<h2 style='color:#4CAF50;'>Trip Details</h2>");
    titleLabel->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(titleLabel);

    // Informatii generale
    QLabel* generalInfo = new QLabel();
    QString infoText;
    infoText += "<b>Trip ID:</b> " + QString::number(trip->getTripId()) + "<br>";
    infoText += "<b>Start Date:</b> " + trip->getStartDate() + "<br>";
    infoText += "<b>End Date:</b> " + trip->getEndDate() + "<br>";
    infoText += "<b>Duration:</b> " + QString::number(trip->getDuration()) + " days<br>";
    infoText += "<b>Added:</b> " + QString(trip->getIsAdded() ? "Yes" : "No") + "<br>";
    infoText += "<b>Total Cost:</b> " + QString::number(trip->getTotalCost(), 'f', 2) + " EUR<br><br>";

    // Nr elemente
    infoText += "<b>Accommodations:</b> " + QString::number(trip->getIdAcc().size()) + "<br>";
    infoText += "<b>Attractions:</b> " + QString::number(trip->getIdAtt().size()) + "<br>";
    infoText += "<b>Routes:</b> " + QString::number(trip->getIdRou().size()) + "<br>";
    generalInfo->setText(infoText);
    generalInfo->setStyleSheet("color: #e0e0e0; background-color: #2d2d2d; padding: 12px; border-radius: 8px;");
    generalInfo->setTextFormat(Qt::RichText);
    generalInfo->setWordWrap(true);
    scrollLayout->addWidget(generalInfo);

    // Obtine datele pentru fiecare zi
    QLabel* itineraryTitle = new QLabel("<h3 style='color:#4CAF50;'>Daily Itinerary</h3>");
    itineraryTitle->setAlignment(Qt::AlignCenter);
    scrollLayout->addWidget(itineraryTitle);

    // Pentru fiecare zi, afisam detaliile
    QDate startDate = QDate::fromString(trip->getStartDate(), "yyyy-MM-dd");

    // Pregatim colectiile de elemente pentru distribuire exacta
    QVector<int> accIds = trip->getIdAcc();
    QVector<int> attIds = trip->getIdAtt();
    QVector<int> routeIds = trip->getIdRou();

    for (int day = 1; day <= trip->getDuration(); ++day) {
        QDate currentDate = startDate.addDays(day - 1);

        // Crearea unui grup expandabil pentru fiecare zi
        QGroupBox* dayGroup = new QGroupBox("Day " + QString::number(day) + " - " + currentDate.toString("dd MMMM yyyy"));
        dayGroup->setStyleSheet("QGroupBox { color: #4CAF50; font-weight: bold; border: 1px solid #3d3d3d; border-radius: 8px; margin-top: 10px; } "
                                "QGroupBox::title { subcontrol-origin: margin; left: 10px; padding: 0 5px; }");
        QVBoxLayout* dayLayout = new QVBoxLayout(dayGroup);

        // CAZARE pentru ziua curenta - exact una per zi
        QLabel* accLabel = new QLabel("<b style='color:#4CAF50;'>Accommodation:</b>");
        dayLayout->addWidget(accLabel);

        if (day <= accIds.size()) {
            Accommodation* acc = findAccommodationById(accIds[day-1]);
            if (acc) {
                QWidget* accWidget = createAccommodationWidget(acc);
                dayLayout->addWidget(accWidget);
            } else {
                QLabel* noAccLabel = new QLabel("Accommodation information not available.");
                noAccLabel->setStyleSheet("color: #a0a0a0; margin-left: 15px;");
                dayLayout->addWidget(noAccLabel);
            }
        } else {
            QLabel* noAccLabel = new QLabel("No accommodation scheduled for this day.");
            noAccLabel->setStyleSheet("color: #a0a0a0; margin-left: 15px;");
            dayLayout->addWidget(noAccLabel);
        }

        // ATRACTIE pentru ziua curenta - exact una per zi
        QLabel* attLabel = new QLabel("<b style='color:#4CAF50;'>Attraction:</b>");
        dayLayout->addWidget(attLabel);

        if (day <= attIds.size()) {
            Attraction* att = findAttractionById(attIds[day-1]);
            if (att) {
                QWidget* attWidget = createAttractionWidget(att);
                dayLayout->addWidget(attWidget);
            } else {
                QLabel* noAttLabel = new QLabel("Attraction information not available.");
                noAttLabel->setStyleSheet("color: #a0a0a0; margin-left: 15px;");
                dayLayout->addWidget(noAttLabel);
            }
        } else {
            QLabel* noAttLabel = new QLabel("No attraction scheduled for this day.");
            noAttLabel->setStyleSheet("color: #a0a0a0; margin-left: 15px;");
            dayLayout->addWidget(noAttLabel);
        }

        // RUTA pentru ziua curenta - exact una per zi
        QLabel* routeLabel = new QLabel("<b style='color:#4CAF50;'>Transportation Route:</b>");
        dayLayout->addWidget(routeLabel);

        if (day <= routeIds.size()) {
            TransportationRoute* route = findRouteById(routeIds[day-1]);
            if (route) {
                QWidget* routeWidget = createRouteWidget(route);
                dayLayout->addWidget(routeWidget);
            } else {
                QLabel* noRouteLabel = new QLabel("Transportation route information not available.");
                noRouteLabel->setStyleSheet("color: #a0a0a0; margin-left: 15px;");
                dayLayout->addWidget(noRouteLabel);
            }
        } else {
            QLabel* noRouteLabel = new QLabel("No transportation route scheduled for this day.");
            noRouteLabel->setStyleSheet("color: #a0a0a0; margin-left: 15px;");
            dayLayout->addWidget(noRouteLabel);
        }

        scrollLayout->addWidget(dayGroup);
    }

    scrollArea->setWidget(scrollContent);
    mainLayout->addWidget(scrollArea);

    // Container pentru butoane
    QWidget* buttonContainer = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonContainer);

    // Buton de confirmare - actualizeaza textul in functie de starea confirmarii
    QPushButton* confirmButton = new QPushButton(trip->getIsAdded() ? "Already Added to Trips" : "Add to Trips");
    confirmButton->setFixedSize(140, 40);
    confirmButton->setStyleSheet(R"(
        QPushButton {
            background-color: )" + QString(trip->getIsAdded() ? "#808080" : "#2196F3") + R"(;
            color: white;
            border-radius: 8px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: )" + QString(trip->getIsAdded() ? "#707070" : "#1976D2") + R"(;
        }
    )");
    buttonLayout->addWidget(confirmButton);

    // Buton de inchidere
    QPushButton* closeButton = new QPushButton("Close");
    closeButton->setFixedSize(120, 40);
    closeButton->setStyleSheet(R"(
        QPushButton {
            background-color: #4CAF50;
            color: white;
            border-radius: 8px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #45A049;
        }
    )");
    buttonLayout->addWidget(closeButton);

    mainLayout->addWidget(buttonContainer, 0, Qt::AlignCenter);

    // Conectarea butonului de inchidere
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);

    // Conectarea butonului de confirmare
    connect(confirmButton, &QPushButton::clicked, [=]() {
        // Verifica daca calatoria este deja confirmata
        if (trip->getIsAdded()) {
            QMessageBox::information(dialog, "Already Added To Trips",
                                     "This trip is already added!");
            return;
        }

        // intreaba utilizatorul daca doreste sa confirme calatoria
        QMessageBox confirmBox;
        confirmBox.setWindowTitle("Add Trip");
        confirmBox.setText("Are you sure you want to confirm this trip?");
        confirmBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        confirmBox.setDefaultButton(QMessageBox::No);
        confirmBox.setIcon(QMessageBox::Question);

        int ret = confirmBox.exec();

        if (ret == QMessageBox::Yes) {
            // Setarea calatoriei ca fiind confirmata
            trip->setIsAdded(true);

            //trimitere si la server
            QJsonObject sendConfirmObj;
            sendConfirmObj["action"] = "CONFIRM_SELECTED_GENERATED_TRIP";
            sendConfirmObj["tripID"] = trip->getTripId();
            //Convert to text(For sending)
            QJsonDocument doc(sendConfirmObj);
            QByteArray jsonData = doc.toJson(QJsonDocument::Compact);  // sau .Indented
            const char* jsonCharPtr = jsonData.constData();

            qDebug() << jsonData;

            Socket* sock = Socket::getInstance();
            sock->sendMessage(jsonCharPtr);

            // Actualizez UI-ul
            QString newInfoText = generalInfo->text();
            newInfoText.replace(
                "<b>Added:</b> No<br>",
                "<b>Added:</b> Yes<br>"
                );
            generalInfo->setText(newInfoText);

            QMessageBox::information(dialog, "Success", "Trip has been added successfully!");
        }
    });

    dialog->exec();
}

void clientWindow::showGeneratedTrips(QJsonObject objData)
{
    Socket* sock = Socket::getInstance();
    IRequest *ack = FactoryRequest::ackReq();

    if(objData["number"].toInt() == 0)
    {
        QLabel* bigLabel = new QLabel(this);
        bigLabel->setText("✈️ Nu exista elemente care satisfac conditiile! ✈️");

        QFont font;
        font.setPointSize(36);
        font.setBold(true);
        bigLabel->setFont(font);
        bigLabel->setAlignment(Qt::AlignCenter);
        bigLabel->setGeometry(this->rect());

        bigLabel->setStyleSheet(R"(
            background-color: rgba(0, 0, 0, 180);
            color: white;
            border-radius: 20px;
            padding: 30px;
        )");

        bigLabel->show();

        QGraphicsOpacityEffect* effect = new QGraphicsOpacityEffect(bigLabel);
        bigLabel->setGraphicsEffect(effect);

        QPropertyAnimation* animation = new QPropertyAnimation(effect, "opacity");
        animation->setDuration(1000);
        animation->setStartValue(1.0);
        animation->setEndValue(0.0);
        animation->setEasingCurve(QEasingCurve::OutQuad);

        connect(animation, &QPropertyAnimation::finished, bigLabel, [=]() {
            bigLabel->hide();
            bigLabel->deleteLater();
        });

        QTimer::singleShot(3000, animation, SLOT(start()));
        sock->sendMessage(ack->getRequest());
        return;
    }

    for (Trip* t : tripsGenerated)
        delete t;
    tripsGenerated.clear();

    // dialog(fereastra) cu lista de tripuri generate
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Tripuri Generate");
    dialog->resize(700, 500);

    QVBoxLayout* mainLayout = new QVBoxLayout(dialog);
    QScrollArea* scrollArea = new QScrollArea(dialog);
    QWidget* scrollWidget = new QWidget();
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);

    QJsonArray tripsArray = objData["GeneratedTrips"].toArray();

    for (int i = 0; i < tripsArray.size(); ++i) {
        QJsonObject tripObj = tripsArray[i].toObject();

        int id = tripObj["id"].toInt();
        QString start = tripObj["startingDate"].toString();
        QString end = tripObj["endingDate"].toString();
        int duration = tripObj["duration"].toInt();
        double cost = tripObj["totalCost"].toDouble();
        bool confirmed = tripObj["isConfirmed"].toBool();

        QVector<int> acc = jsonArrayToQVector(tripObj["accommodations"].toArray());
        QVector<int> att = jsonArrayToQVector(tripObj["attractions"].toArray());
        QVector<int> rou = jsonArrayToQVector(tripObj["routes"].toArray());

        Trip* trip = new Trip(acc, att, rou, id, start, end, duration, confirmed, cost);
        tripsGenerated.append(trip);

        // widget pentru fiecare trip
        QWidget* tripWidget = new QWidget();
        QHBoxLayout* tripLayout = new QHBoxLayout(tripWidget);

        QLabel* infoLabel = new QLabel(
            QString("Trip #%1 | %2 - %3 | %4 zile | Cost: %5 lei")
                .arg(id).arg(start).arg(end).arg(duration).arg(cost));

        QPushButton* detailsButton = new QPushButton("Detalii");
        connect(detailsButton, &QPushButton::clicked, this, [=]() {
            this->showGeneratedTripDetails(trip);
        });

        tripLayout->addWidget(infoLabel);
        tripLayout->addStretch();
        tripLayout->addWidget(detailsButton);

        scrollLayout->addWidget(tripWidget);
    }

    scrollWidget->setLayout(scrollLayout);
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    QPushButton* closeButton = new QPushButton("Închide");
    connect(closeButton, &QPushButton::clicked, dialog, &QDialog::accept);
    mainLayout->addWidget(closeButton);

    sock->sendMessage(ack->getRequest());
    qDebug()<<"ACK";

    dialog->setLayout(mainLayout);
    dialog->exec();

}

void clientWindow::on_autoBut_clicked()
{
    if(canBook)
    {
        this->zile = startDate.daysTo(endDate) + 1;
        historyLabel->hide();
        historyButton->hide();
        questionLabel->hide();
        particularButton->hide();
        automaticLabel->move(330, 15);
        autoButton->hide();
        autoBackButton->show();

        if(mainWidget==nullptr)
        {
        this->mainWidget = new QWidget(this);

        QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
        mainLayout->setAlignment(Qt::AlignCenter);

        // Departure
        QGroupBox *departureBox = new QGroupBox("Departure");
        QVBoxLayout *departureLayout = new QVBoxLayout(departureBox);

        QLineEdit *departureEdit = new QLineEdit;
        departureEdit->setPlaceholderText("Enter departure city");
        departureEdit->setStyleSheet("QLineEdit { padding: 5px; border: 2px solid gray; border-radius: 5px; }"
                                     "QLineEdit:focus { border: 2px solid #0078d7; }");

        departureLayout->addWidget(new QLabel("City:"));
        departureLayout->addWidget(departureEdit);
        departureBox->setLayout(departureLayout);
        mainLayout->addWidget(departureBox);

        // Destination Filters
        QGroupBox *destinationBox = new QGroupBox("Destination Filters");
        QVBoxLayout *destinationLayout = new QVBoxLayout(destinationBox);

        QLineEdit *countryEdit = new QLineEdit;
        countryEdit->setPlaceholderText("Any or type a country");
        countryEdit->setStyleSheet("QLineEdit { padding: 5px; border: 2px solid gray; border-radius: 5px; }"
                                   "QLineEdit:focus { border: 2px solid #0078d7; }");

        QListWidget *climateList = new QListWidget;
        climateList->addItems({"Any", "Snowing", "Sunny"});
        climateList->setSelectionMode(QAbstractItemView::SingleSelection);

        destinationLayout->addWidget(new QLabel("Country:"));
        destinationLayout->addWidget(countryEdit);
        destinationLayout->addWidget(new QLabel("Climate:"));
        destinationLayout->addWidget(climateList);
        destinationBox->setLayout(destinationLayout);
        mainLayout->addWidget(destinationBox);

        // Attraction Filters
        QGroupBox *attractionBox = new QGroupBox("Attraction Filters");
        QVBoxLayout *attractionLayout = new QVBoxLayout(attractionBox);

        QListWidget *categoryList = new QListWidget;
        categoryList->addItems({"Any", "MUSICAL", "RELIGIOUS", "CULTURAL"});
        categoryList->setSelectionMode(QAbstractItemView::MultiSelection);

        attractionLayout->addWidget(new QLabel("Category:"));
        attractionLayout->addWidget(categoryList);
        attractionBox->setLayout(attractionLayout);
        mainLayout->addWidget(attractionBox);

        // Accommodation Filters
        QGroupBox *accommodationBox = new QGroupBox("Accommodation Filters");
        QVBoxLayout *accommodationLayout = new QVBoxLayout(accommodationBox);

        QListWidget *typeList = new QListWidget;
        typeList->addItems({"Any", "HOTEL", "APARTAMENT", "PENSIUNE"});
        typeList->setSelectionMode(QAbstractItemView::MultiSelection);

        accommodationLayout->addWidget(new QLabel("Type:"));
        accommodationLayout->addWidget(typeList);
        accommodationBox->setLayout(accommodationLayout);
        mainLayout->addWidget(accommodationBox);

        // Generate Button
        QPushButton *generateButton = new QPushButton("Generate");
        generateButton->setStyleSheet("QPushButton { background-color: #0078d7; color: white; padding: 8px 16px; border-radius: 6px; }"
                                      "QPushButton:hover { background-color: #005fa3; }");
        mainLayout->addWidget(generateButton);

        // On Generate Clicked
        QObject::connect(generateButton, &QPushButton::clicked, this, [=]() {
            QString departureCity = departureEdit->text().trimmed();
            QString country = countryEdit->text().trimmed();

            QString climate = "Any";
            if (climateList->currentItem() && climateList->currentItem()->text() != "Any")
                climate = climateList->currentItem()->text();

            QStringList categories;
            for (QListWidgetItem *item : categoryList->selectedItems()) {
                categories << item->text();
            }
            if (categories.isEmpty()) categories << "Any";

            QStringList types;
            for (QListWidgetItem *item : typeList->selectedItems()) {
                types << item->text();
            }
            if (types.isEmpty()) types << "Any";

            if (departureCity.isEmpty()) departureCity = "Any";
            if (country.isEmpty()) country = "Any";

            // QJsonObject formatat
            QJsonObject jsonObj;
            jsonObj["username"]= username;
            jsonObj["Country"] = country;
            jsonObj["Climate"] = climate;
            jsonObj["Departure"] = departureCity;
            jsonObj["Category"] = QJsonArray::fromStringList(categories);
            jsonObj["Type"] = QJsonArray::fromStringList(types);
            jsonObj["StartingDate"] = startDate.toString("yyyy-MM-dd");
            jsonObj["EndingDate"] = endDate.toString("yyyy-MM-dd");
            jsonObj["Duration"] = this->zile;
            jsonObj["action"] = "GENERATE_TRIPS";

            QJsonDocument doc(jsonObj);
            QByteArray jsonData = doc.toJson(QJsonDocument::Compact);
            const char* jsonCharPtr = jsonData.constData();

            qDebug() << jsonData;

            Socket* sock = Socket::getInstance();
            sock->sendMessage(jsonCharPtr);

            int size;
            QJsonObject objSize = sock->receiveMessage();
            size = objSize["size"].toInt();

            IRequest *ack = FactoryRequest::ackReq();
            sock->sendMessage(ack->getRequest());

            QJsonObject objData = sock->receiveBigData(size);
            this->showGeneratedTrips(objData);
        });

        mainWidget->setLayout(mainLayout);
        mainWidget->setFixedSize(500, 560);
        mainWidget->move(320, 140);
        mainWidget->show();
    }
        else
        {
            mainWidget->show();
        }
    }
    else
    {
        QLabel *labelWarning = new QLabel(this);
        labelWarning->setText("Select the period from the calendar widget!");

        QFont font;
        font.setFamily("Arial");
        font.setPointSize(12);
        font.setBold(true);

        labelWarning->setFont(font);

        labelWarning->setStyleSheet(
            "color: white; "
            "background-color: #FF6347; "
            "border: 1px solid #D32F2F; "
            "border-radius: 5px; "
            "padding: 8px; "
            );

        labelWarning->move(810,320);
        labelWarning->adjustSize();
        labelWarning->setFixedHeight(40);
        labelWarning->show();
        QTimer::singleShot(2000, this, [=]() {
            labelWarning->hide();
            labelWarning->deleteLater();
        });
    }

}

void clientWindow::on_autoBackBut_clicked()
{    
    this->clearHighlightedDates();
    canBook=false;
    this->zile = 0;
    ziCurenta = 0;


    questionLabel->setText("Want to book a vacation? Click here ! Select your period from the calendar widget!");
    automaticLabel->setText("Want to generate a random trip? Click here! Select your period from the calendar widget!");
    historyLabel->show();
    historyButton->show();
    questionLabel->show();
    particularButton->show();
    automaticLabel->move(330,275);
    autoButton->show();
    autoBackButton->hide();
    this->mainWidget->hide();

}

