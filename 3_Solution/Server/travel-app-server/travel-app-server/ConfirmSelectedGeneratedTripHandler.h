#pragma once
#include "AHandler.h"
#include "include/json_fwd.hpp"


class ConfirmSelectedGeneratedTripHandler :    public AHandler
{
public:
	ConfirmSelectedGeneratedTripHandler();
	virtual nlohmann::json handle(nlohmann::json& request) override;
};

