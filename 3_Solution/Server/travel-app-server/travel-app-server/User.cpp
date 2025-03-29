#include "User.h"

User::User(std::string username, std::string& password, bool isAdmin)
	:_username{username}, _password{password}, _isAdmin{isAdmin}
{
}

User::~User()
{
}
