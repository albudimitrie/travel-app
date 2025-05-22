#pragma once
#include <string>

class User
{
	std::string _username, _password;
	bool _isAdmin;
	double _balance;
public:
	User() = default;
	User(std::string username, std::string &password , bool isAdmin);
	~User();

	bool admin() const { return _isAdmin; }
	void setBalance(double balance);
	double getBalance()const;
	void setUsername(const std::string& username);
	std::string getUsername()const { return _username; }
	std::string getPassword()const { return _password; }

};

