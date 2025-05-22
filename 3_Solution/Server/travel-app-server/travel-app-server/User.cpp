#include "User.h"

User::User(std::string username, std::string& password, bool isAdmin)
	:_username{username}, _password{password}, _isAdmin{isAdmin}
{
}

User::~User()
{
}

void User::setBalance(double balance)
{
	_balance = balance;
}

double User::getBalance() const
{
	return _balance;
}

void User::setUsername(const std::string& username)
{
	_username = username;
}
