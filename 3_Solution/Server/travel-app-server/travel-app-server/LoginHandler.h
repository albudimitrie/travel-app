#pragma once
#include "AHandler.h"
#include "include/json_fwd.hpp"
class LoginHandler :    public AHandler
{
protected:
public:
	LoginHandler();
	virtual nlohmann::json handle(nlohmann::json& request)override;

};

