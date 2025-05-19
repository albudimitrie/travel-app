#pragma once
#include "AHandler.h"
#include "include/json_fwd.hpp"

class TCPServer;

class GetAllRoutesHandler :    public AHandler
{
	TCPServer& _server;
public:
	GetAllRoutesHandler(TCPServer &server);
	virtual nlohmann::json handle(nlohmann::json& request) override;
};

