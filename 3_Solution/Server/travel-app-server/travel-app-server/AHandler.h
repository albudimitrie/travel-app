#pragma once
#include "iHandler.h"
#include "Logger.h"
#include "include/json_fwd.hpp"
class AHandler :    public iHandler
{
protected:
	std::string _reqType;
public:
	virtual std::string getReqIdentifier() override;
	virtual ~AHandler() = default;
};

