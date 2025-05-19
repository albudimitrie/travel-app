#pragma once
#include "AHandler.h"
#include "include/json_fwd.hpp"
class AddCustomTripHandler :
    public AHandler
{
public:
    AddCustomTripHandler();
    virtual nlohmann::json handle(nlohmann::json& request) override;
};

