#include "GetTripConfirmation.h"
#include "include/json.hpp"
#include "TripRepository.h"

using json = nlohmann::json;

GetTripConfirmation::GetTripConfirmation()
{
	this->_reqType = "TRIP_CONFIRM";
}

nlohmann::json GetTripConfirmation::handle(nlohmann::json& request)
{
	TripRepository repo;
	int id_trip = request["trip_id"];
	repo.confirmTrip(id_trip);
	return json();
}
