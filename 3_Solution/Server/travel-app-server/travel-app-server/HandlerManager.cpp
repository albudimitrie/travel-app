#include "HandlerManager.h"
#include "iHandler.h"
#include "include/json.hpp"
#include "Logger.h"

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
		Logger::getInstance()->logResponse(LogStatus::ERROR_, "Request not recognized");
	}
	return worker->handle(request);
}
