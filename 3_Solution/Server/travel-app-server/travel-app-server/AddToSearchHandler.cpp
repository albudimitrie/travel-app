#include "AddToSearchHandler.h"
#include "include/json.hpp"
#include "UserRepository.h"

AddToSearchHandler::AddToSearchHandler()
{
	this->_reqType = "ADD_SEARCH_CONTENT";
}

nlohmann::json AddToSearchHandler::handle(nlohmann::json& request)
{

	try
	{
		UserRepository u_repo;
		std::string type, username, content, content_for_insert;
		type = request["type"];
		username = request["username"];
		content = request["search"];
		content_for_insert = type + ":" + content;
		if(content!="")
			u_repo.addNewSearch(username, content_for_insert);
		return nlohmann::json{};

	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return nlohmann::json{};
	}
}
