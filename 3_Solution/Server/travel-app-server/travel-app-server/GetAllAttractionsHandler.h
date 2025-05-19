#pragma once
#include "AHandler.h"
#include "include/json_fwd.hpp"
class TCPServer;

class GetAllAttractionsHandler :    public AHandler
{
	TCPServer& _server;
public:
	GetAllAttractionsHandler(TCPServer &server);
	virtual nlohmann::json handle(nlohmann::json& request) override;
};

