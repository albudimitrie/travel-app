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

    widAcc=ui->scrollAreaWidgetContents;
    widAtt=ui->scrollAreaWidgetContents_2;
    widTra=ui->scrollAreaWidgetContents_3;
    widAcc->setLayout(new QVBoxLayout());
    widAtt->setLayout(new QVBoxLayout());
    widTra->setLayout(new QVBoxLayout());

    butAcc = ui->pushAcc;
    butAtt = ui->pushAtt;
    butTra = ui->pushTra;

    //scrollAcc->hide();
    scrollAtt->hide();
    scrollTra->hide();

    designScroller(scrollAcc);
    designScroller(scrollAtt);
    designScroller(scrollTra);

    butAcc->setCheckable(true);
    butAtt->setCheckable(true);
    butTra->setCheckable(true);
    butAcc->toggle();

    populateAccColumn(widAcc);


}

clientWindow::~clientWindow()
{
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

        QLabel* label=new QLabel();

        hLayout->addWidget(label);

        Destination * dest = accommodations[i]->destination();

        this->formatLabel(label,accommodations[i],dest);

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

        QPushButton* button1=new QPushButton();

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


    int n = object["size"].toInt();
     //qDebug() << n;
     QJsonArray values = object["values"].toArray();
     //for(int i=0; i < n ;i++)
     //{
     //   qDebug() << values[i];
     //}
    sock->sendMessage(ack->getRequest());
    for(int i=0;i<n;i++)
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


        IRequest* getPhoto = FactoryRequest::photoaccomodationReq(values[i].toInt());
        sock->sendMessage(ack->getRequest());
        sock->sendMessage(getPhoto->getRequest());
        QJsonObject numberObj = sock->receiveMessage();
        int size = numberObj["size"].toInt();

        //qDebug() << size <<"\n";

        QString photo="";
        sock->sendMessage(ack->getRequest());
        QJsonObject frame = sock->receivePhoto(size);
        photo.append(frame["encoded"].toString());

        //qDebug() <<"SIZEUL: "<< photo.size();
        acc->setBase64Data(photo);
        accommodations.push_back(acc);

        sock->sendMessage(ack->getRequest());
    }
}

void clientWindow::formatLabel(QLabel *label, Accommodation *acc, Destination *dest) {
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

