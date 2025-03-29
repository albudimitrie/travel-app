#include "iHandler.h"
#include "LoginHandler.h"
#include "RegisterHandler.h"

iHandler* FactoryHandlers::makeLoginHandler()
{
	return new LoginHandler();
}

iHandler* FactoryHandlers::makeRegisterHandler()
{
	return new RegisterHandler();
}
