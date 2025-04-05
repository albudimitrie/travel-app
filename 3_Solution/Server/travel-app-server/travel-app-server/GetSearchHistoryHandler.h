#pragma once
#include "AHandler.h"
class GetSearchHistoryHandler :    public AHandler
{
public:
	GetSearchHistoryHandler();
	virtual nlohmann::json handle(nlohmann::json& request)override;
};

