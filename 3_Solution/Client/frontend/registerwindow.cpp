#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QVBoxLayout>
#include <QLayout>
#include "factoryrequest.h"
#include "Socket.h"
#include <QTimer>
#include"QPropertyAnimation"

registerWindow::registerWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::registerWindow)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
    layout->addWidget(ui->groupBox, 0, Qt::AlignCenter);
    ui->centralwidget->setLayout(layout);

    ui->groupBox->setMinimumSize(700, 400);  // Set MINIMUM Dimension
    ui->groupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


    ui->lineEdit_2->setEchoMode(QLineEdit::Password);

    QPixmap pixmap(":/images/assets/closed.png");
    //qDebug() << "Image size:" << pixmap.size();
    if (pixmap.isNull()) {
        qDebug() << "Eroare: Imaginea nu a fost încărcată!";
    } else {
        ui->toolButton->setIcon(QIcon(pixmap));
        ui->toolButton->setIconSize(QSize(24, 24));
        ui->toolButton->setFixedSize(30, 35);
    }
    //ui->toolButton->setAutoRaise(true);
    ui->toolButton->setStyleSheet(
        "QToolButton { background-color: transparent; border: none; }"
        "QToolButton:hover { background-color: rgba(200, 200, 200, 30); }"
        "QToolButton:pressed { background-color: rgba(180, 180, 180, 50); }"
        );
    //ui->toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly);

}

registerWindow::~registerWindow()
{
    delete ui;
}

void registerWindow::on_pushButton_clicked()
{
    IRequest *ack = FactoryRequest::ackReq();
   // this->hide();       // Hide register window
   // emit backToLogin(); // Emit the signal to notify the login window to display
    IRequest *regReq = FactoryRequest::registerReq(ui->lineEdit->text(),ui->lineEdit_2->text());

    Socket* sock = Socket::getInstance();

    qDebug() << regReq->getRequest();

    sock->sendMessage(regReq->getRequest());

    QJsonObject obj=sock->receiveMessage();

    sock->sendMessage(ack->getRequest());

    if(obj["status"]=="succesful")
    {
        ui->label_3->setText("Registration successful!");
        ui->label_3->setStyleSheet("color: green;");
        ui->label_3->setVisible(true);

        QTimer::singleShot(3000, this, [=](){
         ui->label_3->setVisible(false);
            this->hide();       // Hide register window
            emit backToLogin(); // Emit the signal to notify the login window to display
        });
    }
    else
    {
        ui->label_3->setText("Username taken . Please try other username!");
        ui->label_3->setStyleSheet("color: red;");
        ui->label_3->setVisible(true);

        QTimer::singleShot(3000, this, [=](){
         ui->label_3->setVisible(false);
        });
    }

}

void registerWindow::on_pushButton_2_clicked()
{
    this->hide();       // Hide register window
    emit backToLogin(); // Emit the signal to notify the login window to display
}


void registerWindow::on_toolButton_clicked()
{
    isPasswordVisible = !isPasswordVisible;
    QPixmap pixmap(isPasswordVisible ? ":/images/assets/opened.png" : ":/images/assets/closed.png");
    ui->toolButton->setIcon(QIcon(pixmap));
    ui->lineEdit_2->setEchoMode(isPasswordVisible ? QLineEdit::Normal : QLineEdit::Password);
}

