#pragma once
#include "AHandler.h"
#include "include/json_fwd.hpp"


class RegisterHandler :    public AHandler
{
public:
	RegisterHandler();
	virtual nlohmann::json handle(nlohmann::json& request) override;
};

