#include "LogoutHandler.h"
#include "include/json.hpp"
#include "UserRepository.h"
#include "User.h"

using json = nlohmann::json;

LogoutHandler::LogoutHandler()
{
	this->_reqType = "LOG_OUT";
}

nlohmann::json LogoutHandler::handle(nlohmann::json& request)
{
	try {
		UserRepository u_repo;
		json reply;
		std::string username;
		double balance;
		User* user = new User{};
		user->setUsername(request["username"]);
		user->setBalance(request["balance"]);
		u_repo.update(*user);
		reply["status"] = "succesful";
		Logger::getInstance()->logResponse(LogStatus::SUCCES, "Logged out with succes");
		delete user;
		return reply;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return json{};
	}

}
