#pragma once
#include "AHandler.h"
class TCPServer;
class GetTripHistoryHandler :    public AHandler
{
	TCPServer& _server;
public:
	GetTripHistoryHandler(TCPServer& server);
	virtual nlohmann::json handle(nlohmann::json& request) override;

};

