#pragma once
#include "AHandler.h"
#include "include/json_fwd.hpp"
class GetAccommodationWithIDHandler :    public AHandler
{
public:
	GetAccommodationWithIDHandler();
	virtual nlohmann::json handle(nlohmann::json& request) override;
};

