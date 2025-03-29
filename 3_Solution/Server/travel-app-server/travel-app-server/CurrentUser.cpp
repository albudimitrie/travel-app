#include "CurrentUser.h"

CurrentUser* CurrentUser::instance = nullptr;

CurrentUser* CurrentUser::getInstance()
{
	if (!instance)
	{
		instance = new CurrentUser;
    }
	return instance;
}

void CurrentUser::destroyInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void CurrentUser::setActive(User* user)
{
	this->_current = user;
}

void CurrentUser::disconnect()
{
	this->_current = nullptr;
}
