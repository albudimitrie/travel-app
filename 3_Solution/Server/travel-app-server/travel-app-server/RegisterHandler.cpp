#include "RegisterHandler.h"

#include "include/json.hpp"

#include "User.h"
#include "UserRepository.h"
#include "utils.h"

#include <iostream>


using json = nlohmann::json;

RegisterHandler::RegisterHandler()
{
	this->_reqType = "REGISTER";
}

nlohmann::json RegisterHandler::handle(nlohmann::json& request)
{
	UserRepository users;
	json reply;

	std::string username, password;
	username = request["username"];
	password = request["password"];

	if (users.isUsernameTaken(username) || utils::hasIllegalLoginChars(username))
	{
		reply["status"] = "unsuccesful";
		std::string log = "Register failed[" + username + ":" + password + "]";
		Logger::getInstance()->logResponse(LogStatus::ERROR_, log);
	}
	else
	{
		reply["status"] = "succesful";
		User* user = new User{ username, password, false };
		try
		{
			users.create(*user);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << "\n";
		}
		std::string log = "Register with succes[" + username  + "]";
		Logger::getInstance()->logResponse(LogStatus::SUCCES, log);
	}

	return reply;
}
