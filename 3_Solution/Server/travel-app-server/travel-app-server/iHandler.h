#pragma once

#include "include/json_fwd.hpp"
#include <string>


class TCPServer;

//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
class iHandler
{
protected:
public:

	virtual nlohmann::json handle(nlohmann::json& request) = 0;
	virtual std::string getReqIdentifier() = 0;
	virtual ~iHandler() = default;

};
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------
class FactoryHandlers
{
public:
	static iHandler* makeLoginHandler();
	static iHandler* makeRegisterHandler();
	static iHandler* makeLogoutHandler();
	static iHandler* makeGetSearchHistoryHandler();
	static iHandler* makeGetNumberAccommodations();
	static iHandler* makeGetAccWithId();
	static iHandler* makeGetPhoto(TCPServer& server);
	static iHandler* makeGetAllAttractions(TCPServer& server);
	static iHandler* makeGetAllRoutesHandler(TCPServer& server);
	static iHandler* makeAddCustomTripHandler();
	static iHandler* makeGetTripHistoryHandler(TCPServer& server);
	static iHandler* makeTripConfirmationHandler();
	static iHandler* makeGenerateTripHandler(TCPServer& server);
	static iHandler* makeConfirmationOfGeneratedTrips();
	static iHandler* makeAddNewSearchHandler();
};
//---------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------