#pragma once
#include "AHandler.h"
#include "include/json_fwd.hpp"


class TCPServer;
class GenerateTripsHandlers :    public AHandler
{
	TCPServer& _server;
public:
	GenerateTripsHandlers(TCPServer &server);
	virtual nlohmann::json handle(nlohmann::json& request) override;
};

