#include "clientwindow.h"
#include "ui_clientwindow.h"
#include"factoryrequest.h"
#include"Socket.h"
#include <QScrollArea>
#include <QScrollBar>

clientWindow::clientWindow(QWidget *parent,QString username)
    : QMainWindow(parent)
    , ui(new Ui::clientWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    this->resize(1400, 700); // Dimensiune inițială
    this->setFixedSize(this->size());
    this->username=username;

    ui->label->setText("Logged as : "+username);
    ui->label->setStyleSheet("color: black;");
    ui->label->setVisible(true);

   /* // Configurează ScrollArea
    scrollArea = ui->scrollArea; // Presupun că ai un scrollArea definit în fișierul UI
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    // Creează widget-ul pentru conținut
    contentWidget = new QWidget(scrollArea);
    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setAlignment(Qt::AlignTop);
    contentLayout->setSpacing(10);
    contentWidget->setLayout(contentLayout);

    // Setează widget-ul pentru scrollArea
    scrollArea->setWidget(contentWidget);

    // Creează și adaugă butoanele pentru scroll (dacă nu sunt deja în UI)
    QPushButton *scrollUpButton = new QPushButton("Scroll Sus", this);
    QPushButton *scrollDownButton = new QPushButton("Scroll Jos", this);

    // Adaugă butoanele la layout-ul principal (presupun că ai un layout central)
    // Ajustează această parte conform structurii UI-ului tău
    QVBoxLayout *mainLayout = qobject_cast<QVBoxLayout*>(centralWidget()->layout());
    if (mainLayout) {
        mainLayout->insertWidget(0, scrollUpButton);
        mainLayout->addWidget(scrollDownButton);
    }

    // Conectează butoanele pentru scrollare
    connect(scrollUpButton, &QPushButton::clicked, this, &clientWindow::scrollUp);
    connect(scrollDownButton, &QPushButton::clicked, this, &clientWindow::scrollDown);

    // Exemplu: Adaugă câteva widget-uri în scrollArea pentru test
    for (int i = 0; i < 10; i++) {
        QLabel *label = new QLabel(QString("Oferta %1").arg(i+1), contentWidget);
        label->setFixedHeight(100);
        label->setAlignment(Qt::AlignCenter);
        label->setStyleSheet("background-color: #f0f0f0; border: 1px solid #ddd;");
        contentLayout->addWidget(label);
    }
*/
}

clientWindow::~clientWindow()
{
    delete ui;
}

void clientWindow::scrollUp()
{
    QScrollBar *vScrollBar = scrollArea->verticalScrollBar();
    int currentValue = vScrollBar->value();
    vScrollBar->setValue(currentValue - 100); // Scroll sus cu 100 pixeli
}

void clientWindow::scrollDown()
{
    QScrollBar *vScrollBar = scrollArea->verticalScrollBar();
    int currentValue = vScrollBar->value();
    vScrollBar->setValue(currentValue + 100); // Scroll jos cu 100 pixeli
}

void clientWindow::on_logout_clicked()
{
    IRequest *logoutReq = FactoryRequest::logoutReq(this->username);

    Socket* sock = Socket::getInstance();

    qDebug() << logoutReq->getRequest();

    sock->sendMessage(logoutReq->getRequest());

    sock->receiveMessage();

    this->hide();       // Hide register CLIENT
    emit backToLogin(); // emit the signal to notify the login window to display
\

}


void clientWindow::on_searchButton_clicked()
{

}


