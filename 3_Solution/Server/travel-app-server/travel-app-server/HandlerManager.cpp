#include "HandlerManager.h"
#include "iHandler.h"
#include "include/json.hpp"

void HandlerManager::addHandler(iHandler* handler)
{
	if (handler->getReqIdentifier().empty())
	{
		throw 1;
	}
	_mappings[handler->getReqIdentifier()] = handler;
}

nlohmann::json HandlerManager::processRequest(nlohmann::json& request)
{
	iHandler* worker = nullptr;
	std::string action = request["action"];
	worker = _mappings[action];
	if (!worker)
	{
		throw 1;
	}
	return worker->handle(request);
}
