#include "GetAccommodationWithIDHandler.h"
#include "include\json.hpp"
#include "iAccommodation.h"
#include "AccommodationRepository.h"
#include "Destination.h"

using json = nlohmann::json;
GetAccommodationWithIDHandler::GetAccommodationWithIDHandler()
{
	this->_reqType = "GET_ACC_WITH_ID";
}

nlohmann::json GetAccommodationWithIDHandler::handle(nlohmann::json& request)
{
	int id = request["id"];
	AccommodationRepository repo;
	iAccommodation* acc = repo.getAccWithID(id);
	json reply;
	reply["AccommodationID"] = id;
	reply["Name"] = acc->getName();
	reply["Type"] = acc->getType();
	reply["Address"] = acc->getAddress();
	reply["Description"] = acc->getDescription();
	reply["PricePerNight"] = acc->getPricePerNight();
	reply["Facilities"] = acc->getFacilities();

	Destination* dest = acc->getDestination();
	reply["DestinationID"] = dest->getId();
	reply["DestinationName"] = dest->getName();
	reply["Country"] = dest->getCountry();
	reply["City"] = dest->getCity();
	reply["DestinationDescription"] = dest->getDescription();
	reply["Climate"] = dest->getClimate();
	reply["IsActive"] = dest->isActive();
	delete acc;
	return reply;



}
