#include "LogoutHandler.h"
#include "include/json.hpp"

using json = nlohmann::json;

LogoutHandler::LogoutHandler()
{
	this->_reqType = "LOG_OUT";
}

nlohmann::json LogoutHandler::handle(nlohmann::json& request)
{
	json reply;
	reply["status"] = "succesful";
	Logger::getInstance()->logResponse(LogStatus::SUCCES, "Logged out with succes");
	return reply;

}
