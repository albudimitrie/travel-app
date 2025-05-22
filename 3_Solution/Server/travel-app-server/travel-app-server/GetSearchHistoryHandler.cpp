#include "GetSearchHistoryHandler.h"
#include "include/json.hpp"
#include "UserRepository.h"
#include <iostream>

using json = nlohmann::json;

GetSearchHistoryHandler::GetSearchHistoryHandler()
{
	this->_reqType = "GET_SEARCH_HISTORY";
}

nlohmann::json GetSearchHistoryHandler::handle(nlohmann::json& request)
{
	UserRepository users;
	std::vector<std::string > sHistory;
	std::string username = request["username"];
	json reply;
	try
	{
		sHistory = users.getLatestSearches(username);
		reply["history"] = sHistory;
	}
	catch (std::exception &e)
	{
		std::cout << e.what()<<"\n";
	}
	return reply;
}
