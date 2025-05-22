#include "walletdialog.h"
#include "wallet.h"
#include <QInputDialog>

WalletDialog::WalletDialog(QWidget *parent,Wallet* wallet) : QDialog(parent)
{
    // Stil general pentru dialog
    this->setStyleSheet(R"(
    QLabel {
        font-size: 18px;
        font-weight: bold;
        color: #2e7d32; /* verde închis */
    }

    QPushButton {
        background-color: #4CAF50;
        color: white;
        border: none;
        border-radius: 10px;
        padding: 8px 16px;
        font-size: 14px;
    }

    QPushButton:hover {
        background-color: #45a049;
    }

    QDialog {
        background-color: #f0fff4;
        border: 2px solid #a5d6a7;
        border-radius: 12px;
    }
)");


    this->wallet=wallet;
    setWindowTitle("💰 Wallet");
    setFixedSize(250, 150);

    balanceLabel = new QLabel(this);
    addFundsButton = new QPushButton("Add Funds", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(balanceLabel);
    layout->addWidget(addFundsButton);

    updateBalanceLabel();

    connect(addFundsButton, &QPushButton::clicked, this, &WalletDialog::onAddFundsClicked);
}

void WalletDialog::updateBalanceLabel()
{
    double bal = wallet->getBalance();
    balanceLabel->setText("Balance: €" + QString::number(bal, 'f', 2));
}

void WalletDialog::onAddFundsClicked()
{
    bool ok;
    double amount = QInputDialog::getDouble(this, "Add Funds", "Amount:", 0, 0, 1000000, 2, &ok);
    if (ok && amount > 0) {
        wallet->modifyBalance(amount);
        updateBalanceLabel();
    }
}
