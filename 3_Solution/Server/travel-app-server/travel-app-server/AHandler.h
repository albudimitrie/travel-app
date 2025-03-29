#pragma once
#include "iHandler.h"
class AHandler :    public iHandler
{
protected:
	std::string _reqType;
public:
	virtual std::string getReqIdentifier() override;
	virtual ~AHandler() = default;
};

