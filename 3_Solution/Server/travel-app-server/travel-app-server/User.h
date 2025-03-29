#pragma once
#include <string>
#include <vector>



class User
{
	std::string _username, _password;
	bool _isAdmin;
	//TODO ALTE CHESTII, ISTORIC CAUTARI, CALAATORII TRECUTE, wallet etc

public:
	User(std::string username, std::string &password , bool isAdmin);
	~User();

	bool admin() const { return _isAdmin; }
	std::string getUsername()const { return _username; }
	std::string getPassword()const { return _password; }

};

