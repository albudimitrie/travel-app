#include "clientwindow.h"
#include "ui_clientwindow.h"
#include "factoryrequest.h"
#include "Socket.h"
#include <QScrollArea>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QLayout>
#include <QLabel>
#include <QPushButton>

clientWindow::clientWindow(QWidget *parent,QString username)
    : QMainWindow(parent)
    , ui(new Ui::clientWindow)
{
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
        backdrop-filter: blur(10px);
    }
)");

    scrollAcc = ui->scrollAreaAccommodations;
    scrollAtt = ui->scrollAreaAttractions;
    scrollTra = ui->scrollAreaTransportation;

    widAcc=ui->scrollAreaWidgetContents;
    widAtt=ui->scrollAreaWidgetContents_2;
    widTra=ui->scrollAreaWidgetContents_3;

    butAcc = ui->pushAcc;
    butAtt = ui->pushAtt;
    butTra = ui->pushTra;

 // scrollAcc->hide();
    scrollAtt->hide();
    scrollTra->hide();

    designScroller(scrollAcc);
    designScroller(scrollAtt);
    designScroller(scrollTra);

    butAcc->setCheckable(true);
    butAtt->setCheckable(true);
    butTra->setCheckable(true);
    butAcc->toggle();

    for(int i=0;i<15;i++)

    {

        QHBoxLayout* hLayout = new QHBoxLayout();

        QVBoxLayout* vLayout = qobject_cast<QVBoxLayout*>(widAcc->layout());

        if (vLayout) {

            vLayout->addLayout(hLayout);

        }

        QLabel* label=new QLabel();

        hLayout->addWidget(label);

        label->setText("TBC...");

        label->setAlignment(Qt::AlignCenter);

        label->setStyleSheet(R"(
    QLabel {
        color: #ffffff;
        background: rgba(255, 255, 255, 0.1);
        border-radius: 15px;
        padding: 8px 16px;
        font-weight: 600;
        backdrop-filter: blur(10px);

    }
)");


        label->setFixedSize(350, 300);

        QPushButton* button1=new QPushButton();

        //QPushButton* button2=new QPushButton();

        hLayout->addWidget(button1);

        //hLayout->addWidget(button2);

        //button2->setText("History");

        button1->setFixedSize(650,300);

        QPixmap pixmap(":/images/assets/LOGO.png");

        QIcon icon(pixmap.scaled(700,300, Qt::KeepAspectRatio, Qt::SmoothTransformation));

        button1->setIcon(icon);

        button1->setIconSize(QSize(700,300));

        button1->setCursor(Qt::PointingHandCursor);

        button1->setStyleSheet(R"(
    QPushButton {
        background: #2e2e2e;
        border-radius: 15px;
        padding: 8px 16px;
        color: #e0e0e0;
        box-shadow:
            5px 5px 15px rgba(0,0,0,0.6),
           -5px -5px 15px rgba(255,255,255,0.1);
    }
    QPushButton:pressed {
        box-shadow:
            inset 5px 5px 15px rgba(0,0,0,0.6),
            inset -5px -5px 15px rgba(255,255,255,0.1);
    }
)");



    }

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
        box-shadow: 0 4px 12px rgba(0,0,0,0.6);
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
    IRequest *logoutReq = FactoryRequest::logoutReq(this->username);

    Socket* sock = Socket::getInstance();

    qDebug() << logoutReq->getRequest();

    sock->sendMessage(logoutReq->getRequest());

    sock->receiveMessage();

    this->hide();       // Hide client window
    emit backToLogin(); // Emit the signal to notify the login window to display
\

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



