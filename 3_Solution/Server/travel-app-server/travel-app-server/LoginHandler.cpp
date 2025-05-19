#include "LoginHandler.h"
#include "include/json.hpp"
#include "UserRepository.h"
#include "User.h"
#include "utils.h"

using json = nlohmann::json;

LoginHandler::LoginHandler()
{
	AHandler::_reqType = "LOG_IN";
}

nlohmann::json LoginHandler::handle(nlohmann::json& request)
{
	json reply;
	UserRepository users;
	std::string username, password;
	User* user = nullptr;


	username = request["username"];
	password = request["password"];

	if (username.empty() || password.empty() || utils::hasIllegalLoginChars(username))
	{
		reply["status"] = "unsuccesful";
		return reply;
	}

	if (users.userExists(username, password))
	{
		reply["status"] = "succesful";
		reply["username"] = username;

		if (users.isAdmin(username, password))
		{
			reply["rights"] = "admin";
			user = new User{ username, password, true };
		}
		else
		{
			reply["rights"] = "regular";
			user = new User{ username, password, false };

		}
		std::string log = "Login with succes[" + username + "]";
		Logger::getInstance()->logResponse(LogStatus::SUCCES, log);
	}
	else
	{
		reply["status"] = "unsuccesful";
		std::string log = "Login failed[" + username + ":" + password + "]";
		Logger::getInstance()->logResponse(LogStatus::ERROR_, log);
	}
	return reply;
}
