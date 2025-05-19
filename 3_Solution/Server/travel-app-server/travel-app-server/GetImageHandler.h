#pragma once
#define  _CRT_SECURE_NO_WARNINGS
#include "AHandler.h"
#include "TCPServer.h"
#include "include/json_fwd.hpp"
class GetImageHandler :    public AHandler
{
	TCPServer& _server;
public:
	GetImageHandler(TCPServer &server);
	virtual nlohmann::json handle(nlohmann::json& request) override;
};

