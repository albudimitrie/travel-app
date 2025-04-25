#include "iHandler.h"
#include "LoginHandler.h"
#include "RegisterHandler.h"
#include "LogoutHandler.h"
#include "GetSearchHistoryHandler.h"

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

iHandler* FactoryHandlers::makeGetSearchHistoryHandler()
{
	return new GetSearchHistoryHandler();
}
