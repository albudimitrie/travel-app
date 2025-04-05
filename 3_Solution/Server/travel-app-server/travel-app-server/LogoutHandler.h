#pragma once
#include "AHandler.h"
class LogoutHandler :    public AHandler
{

public:
	LogoutHandler();
	virtual nlohmann::json handle(nlohmann::json& request) override;
	virtual ~LogoutHandler() = default;
};

