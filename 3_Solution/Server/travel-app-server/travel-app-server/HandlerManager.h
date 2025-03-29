#pragma once
#include <map>
#include <string>
#include "include/json_fwd.hpp"

class iHandler;


class HandlerManager
{
	std::map<std::string, iHandler*> _mappings;
public:
	HandlerManager() = default;
	void addHandler(iHandler* handler);
	nlohmann::json processRequest(nlohmann::json& request);

};

