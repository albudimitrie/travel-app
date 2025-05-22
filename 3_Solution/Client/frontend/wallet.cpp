#include "wallet.h"


Wallet* Wallet::instance = nullptr;

Wallet* Wallet::getInstance(double balance)
{
    if (!instance)
        instance = new Wallet(balance);
    return instance;
}


Wallet::Wallet(double balance)
{
    this->balance=balance;
}
