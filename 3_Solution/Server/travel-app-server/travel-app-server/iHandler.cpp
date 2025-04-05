#include "iHandler.h"
#include "LoginHandler.h"
#include "RegisterHandler.h"
#include "LogoutHandler.h"

iHandler* FactoryHandlers::makeLoginHandler()
{
	return new LoginHandler();
}

iHandler* FactoryHandlers::makeRegisterHandler()
{
	return new RegisterHandler();
}

iHandler* FactoryHandlers::makeLogoutHandler()
{
	return new LogoutHandler();
}
