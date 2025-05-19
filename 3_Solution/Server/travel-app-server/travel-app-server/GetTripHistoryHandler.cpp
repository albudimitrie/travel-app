#include "GetTripHistoryHandler.h"
#include "include/json_fwd.hpp"
#include "TCPServer.h"
#include "Trip.h"
#include "DayTrip.h"
#include "TripRepository.h"
#include <map>
#include "UserRepository.h"
#include "iAccommodation.h"
#include "iAttraction.h"
#include "TransportationRoute.h"
GetTripHistoryHandler::GetTripHistoryHandler(TCPServer& server)
	:_server{server}
{
	this->_reqType = "GET_TRIP_HISTORY";
}

nlohmann::json GetTripHistoryHandler::handle(nlohmann::json& request)
{
	json response;
	response["trips"] = json::array();
	UserRepository u_repo;
	int id_user = u_repo.getIDForUsername(request["username"]);
	TripRepository repo;
	std::vector<Trip*> trips = repo.getAllForUserID(id_user);

	for (Trip* tr : trips)
	{
		json obj;
		std::map<int, DayTrip*> dtrips = tr->getDayTrips();
		std::vector<int> accs;
		std::vector<int> atts;
		std::vector<int >routes;
		for (auto it = dtrips.begin(); it != dtrips.end(); it++)
		{
			accs.push_back(it->second->getAccommodation()->getID());
			atts.push_back(it->second->getAttraction()->getId());
			routes.push_back(it->second->getRoute()->getId());
		}
		obj["accommodations"] = accs;
		obj["attractions"] = atts;
		obj["routes"] = routes;
		obj["startingDate"] = tr->getStartingDate();
		obj["endingDate"] = tr->getEndingDate();
		obj["duration"] = tr->getDuration();
		obj["totalCost"] = tr->getTotalCost();
		obj["isConfirmed"] = tr->isConfirmed();
		obj["id"] = tr->getID();
		response["trips"].push_back(obj);
	}
	response["number"] = trips.size();

	std::string response_str = response.dump();

	json response_size;
	response_size["size"] = response_str.size();

	std::string response_size_str = response_size.dump();

	_server.send_data(response_size_str.c_str());
	_server.send_data(response_str.c_str());

	return nlohmann::json();
}
