#include "iHandler.h"
#include "LoginHandler.h"
#include "RegisterHandler.h"
#include "LogoutHandler.h"
#include "GetSearchHistoryHandler.h"
#include "GetNumberAccomodationsHandler.h"
#include "GetAccommodationWithIDHandler.h"
#include "GetImageHandler.h"
#include "GetAllAttractionsHandler.h"
#include "GetAllRoutesHandler.h"
#include "AddCustomTripHandler.h"
#include "GetTripHistoryHandler.h"
#include "GetTripConfirmation.h"
#include "GenerateTripsHandlers.h"
#include "ConfirmSelectedGeneratedTripHandler.h"

iHandler* FactoryHandlers::makeLoginHandler()
{
	return new LoginHandler();
}

iHandler* FactoryHandlers::makeRegisterHandler()
{
	return new RegisterHandler();
}

iHandler* FactoryHandlers::makeLogoutHandler()
{
	return new LogoutHandler();
}

iHandler* FactoryHandlers::makeGetSearchHistoryHandler()
{
	return new GetSearchHistoryHandler();
}

iHandler* FactoryHandlers::makeGetNumberAccommodations()
{
	return new GetNumberAccomodationsHandler();
}

iHandler* FactoryHandlers::makeGetAccWithId()
{
	return new GetAccommodationWithIDHandler();
}

iHandler* FactoryHandlers::makeGetPhoto(TCPServer &server)
{
	return new GetImageHandler(server);
}

iHandler* FactoryHandlers::makeGetAllAttractions(TCPServer& server)
{
	return new GetAllAttractionsHandler(server);
}

iHandler* FactoryHandlers::makeGetAllRoutesHandler(TCPServer& server)
{
	return new GetAllRoutesHandler(server);
}

iHandler* FactoryHandlers::makeAddCustomTripHandler()
{
	return new AddCustomTripHandler{};
}

iHandler* FactoryHandlers::makeGetTripHistoryHandler(TCPServer& server)
{
	return new GetTripHistoryHandler(server);
}

iHandler* FactoryHandlers::makeTripConfirmationHandler()
{
	return new GetTripConfirmation{};
}

iHandler* FactoryHandlers::makeGenerateTripHandler(TCPServer& server)
{
	return new GenerateTripsHandlers{server};
}

iHandler* FactoryHandlers::makeConfirmationOfGeneratedTrips()
{
	return new ConfirmSelectedGeneratedTripHandler{};
}
