#ifndef WALLETDIALOG_H
#define WALLETDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class Wallet;

class WalletDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WalletDialog(QWidget *parent = nullptr,Wallet *wallet = nullptr);

private slots:
    void onAddFundsClicked();

private:
    Wallet *wallet;
    QLabel *balanceLabel;
    QPushButton *addFundsButton;

    void updateBalanceLabel();
};

#endif // WALLETDIALOG_H
