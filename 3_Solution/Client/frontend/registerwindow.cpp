#include "registerwindow.h"
#include "ui_registerwindow.h"
#include <QVBoxLayout>
#include <QLayout>

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
}

registerWindow::~registerWindow()
{
    delete ui;
}

void registerWindow::on_pushButton_clicked()
{
    this->hide();       // Hide register window
    emit backToLogin(); // emit the signal to notify the login window to display
}

void registerWindow::on_pushButton_2_clicked()
{
    this->hide();       // Hide register WINDOW
    emit backToLogin(); // emit the signal to notify the login window to display
}

