#include "AddCustomTripHandler.h"
#include "include/json.hpp"
#include "Trip.h"
#include "DayTrip.h"
#include "TripRepository.h"
#include "UserRepository.h"
#include <iostream>
#include "iAccommodation.h"
#include "iAttraction.h"
#include "TransportationRoute.h"

using json = nlohmann::json;

AddCustomTripHandler::AddCustomTripHandler()
{
	this->_reqType = "ADD_CUSTOM_TRIP";
}

nlohmann::json AddCustomTripHandler::handle(nlohmann::json& request)
{
	try
	{
		TripRepository repo;
		UserRepository u_repo;
		Trip* trip = new Trip{};

		std::vector<int> accs = request["accommodations"];
		std::vector<int> atts = request["attractions"];
		std::vector<int> routes = request["routes"];
		int duration = request["duration"];
		std::string starting_period = request["starting_date"];
		std::string ending_period = request["ending_date"];
		int user_id = u_repo.getIDForUsername(request["username"]);
		trip->setConfirmed(0);
		trip->setDuration(duration);
		trip->setStartDate(starting_period);
		trip->setEndDate(ending_period);
		trip->setUserID(user_id);
		trip->setTotalCost(0);
		for (int i = 0; i < duration; i++)
		{
			DayTrip* daytrip = new DayTrip;
			daytrip->setDayNumber(i + 1);
			iAccommodation* acc = FactoryAccommodations::makeApartament();
			iAttraction* attr = FactoryAttraction::makeCulturalAttraction();
			TransportationRoute* rt = new TransportationRoute{};
			acc->setId(accs[i]);
			attr->setId(atts[i]);
			rt->setId(routes[i]);
			daytrip->setAccommodation(acc);
			daytrip->setAttraction(attr);
			daytrip->setRoute(rt);
			trip->addDayTrip(i, daytrip);
		}
		repo.create(*trip);
		delete trip;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
	}
	return nlohmann::json();
}
