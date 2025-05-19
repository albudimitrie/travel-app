#pragma once
#include "AHandler.h"
#include "include/json_fwd.hpp"


class GetTripConfirmation :
    public AHandler
{
public:
    GetTripConfirmation();
    virtual nlohmann::json handle(nlohmann::json& request) override;
};

