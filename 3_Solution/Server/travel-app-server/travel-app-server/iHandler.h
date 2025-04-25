#pragma once

#include "include/json_fwd.hpp"
#include <string>


class LoginHandler;
class RegisterHandler;
class LogoutHandler;
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
class iHandler
{
protected:
public:

	virtual nlohmann::json handle(nlohmann::json& request) = 0;
	virtual std::string getReqIdentifier() = 0;
	virtual ~iHandler() = default;

};
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
class FactoryHandlers
{
public:
	static iHandler* makeLoginHandler();
	static iHandler* makeRegisterHandler();
	static iHandler* makeLogoutHandler();
	static iHandler* makeGetSearchHistoryHandler();

};
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------