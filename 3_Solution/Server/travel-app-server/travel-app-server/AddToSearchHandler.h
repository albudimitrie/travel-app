#pragma once
#include "AHandler.h"
#include "include/json_fwd.hpp"

class AddToSearchHandler :    public AHandler
{
public:
	AddToSearchHandler();
	nlohmann::json handle(nlohmann::json& request) override;
};

