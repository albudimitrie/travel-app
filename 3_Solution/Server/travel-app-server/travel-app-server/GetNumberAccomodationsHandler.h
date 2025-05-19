#pragma once
#include "AHandler.h"
class GetNumberAccomodationsHandler :    public AHandler
{
public:
	GetNumberAccomodationsHandler();
	virtual nlohmann::json handle(nlohmann::json& request) override;
};

