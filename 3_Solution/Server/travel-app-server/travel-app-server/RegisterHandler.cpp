#include "RegisterHandler.h"

#include "include/json.hpp"

#include "User.h"
#include "UserRepository.h"


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

	if (!users.isUsernameTaken(username))
	{
		reply["status"] = "unsuccesful";
	}
	else
	{

	}

	return json{};
}
