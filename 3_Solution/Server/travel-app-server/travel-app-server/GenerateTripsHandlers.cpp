#include "TCPServer.h"
#include "GenerateTripsHandlers.h"
#include "include/json.hpp"
#include "AccommodationRepository.h"
#include "AttractionRepository.h"
#include "TransportationRepository.h"
#include "TripRepository.h"
#include "iAttraction.h"
#include "iAccommodation.h"
#include "TransportationRoute.h"
#include "TripService.h"
#include "UserRepository.h"
#include "Trip.h"
#include "DayTrip.h"
#include <iostream>

#define DEFAULT_NUMBER_OF_GENERATED_TRIPS 10



using json = nlohmann::json;

GenerateTripsHandlers::GenerateTripsHandlers(TCPServer& server)
	:_server{server}
{
	this->_reqType = "GENERATE_TRIPS";
	//clientul o sa imi trimita asta cu filtre si eu o sa i trimit 3 excursii generate automat
}

nlohmann::json GenerateTripsHandlers::handle(nlohmann::json& request)
{
	AttractionRepository att_repo;
	AccommodationRepository acc_repo;
	TransportationRepository route_repo;
	TripRepository trip_repo;
	UserRepository u_repo;

	TripService trip_service;

	std::string country, starting_date, ending_date, climate, departure_city, username;
	int duration;
	std::vector<std::string> category_options = request["Category"];
	std::vector<std::string> type_options = request["Type"];
	country = request["Country"];
	starting_date = request["StartingDate"];
	ending_date = request["EndingDate"];
	duration = request["Duration"];
	climate = request["Climate"];
	departure_city = request["Departure"];
	username = request["username"];
	int id_user = u_repo.getIDForUsername(username);

	std::vector<iAttraction*> atractii = att_repo.getAttWithFilters(country, climate, category_options);
	std::vector<iAccommodation*> accommodations = acc_repo.getAccsWithFilters(country, climate, type_options);
	std::vector<TransportationRoute*> routes = route_repo.getAllRoutes();

	trip_service.assignNewEligibleAccommodations(std::move(accommodations));
	trip_service.assignNewEligibleAttractions(std::move(atractii));
	trip_service.assignNewEligibleRoutes(std::move(routes));

	std::vector<Trip*> trips;

	for (int i = 0; i < DEFAULT_NUMBER_OF_GENERATED_TRIPS; i++)
	{
		try
		{
			Trip* generated = trip_service.buildTrip(departure_city, duration, starting_date, ending_date);
			trips.push_back(generated);

		}
		catch (std::exception& e)
		{
			std::cout << e.what() << "\n";
		}
	}
	for (Trip* t : trips)
	{
		t->setUserID(id_user);
		trip_repo.createGeneratedTrip(*t);
	}
	std::vector<int> trip_ids = trip_repo.getMostRecentGeneratedTripsIDS(trips.size());
	for (int i = 0; i < trips.size(); i++)
	{
		trips[i]->setID(trip_ids[i]);
	}
	json response;
	response["GeneratedTrips"] = json::array();
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
		response["GeneratedTrips"].push_back(obj);
	}
	response["number"] = trips.size();
	for (Trip* tr : trips)
	{
		delete tr;
	}
	trips.clear();

	std::string response_str = response.dump();
	std::cout << response_str;
	json response_size;
	response_size["size"] = response_str.size();
	std::string response_size_str = response_size.dump();

	_server.send_data(response_size_str.c_str());
	_server.send_data(response_str.c_str());
	

	return nlohmann::json();
}
