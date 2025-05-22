#ifndef WALLET_H
#define WALLET_H

class Wallet
{
private:
    double balance = 0;

    static Wallet* instance;
public:
    Wallet(const Wallet&) = delete;
    Wallet& operator=(const Wallet&) = delete;

    static Wallet* getInstance(double balance);

    Wallet(double balance);//cons
    void setBalance(double balance)
    {
        this->balance=balance;
    }
    double getBalance()
    {
        return balance;
    }
    void modifyBalance(double amount)
    {
        balance += amount;
    }
    void dischargeBalance(double amount)
    {
        balance -= amount;
    }
    static void destroyInstance()
    {
        if(instance)
        {
            delete instance;
        }
        instance = nullptr;
    }
};

#endif // WALLET_H
