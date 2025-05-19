#include "TripService.h"
#include "iAccommodation.h"
#include "iAttraction.h"
#include "iTransportation.h"
#include "TransportationRoute.h"
#include "Destination.h"
#include "Trip.h"
#include "DayTrip.h"
#include "TransportationRepository.h"

void TripService::filterLocations()
{
	for (int i = 0; i < _eligibleAtts.size(); i++)
	{
		if (!hasAccinAttCity(_eligibleAtts[i]->getDestination()->getCity()))
		{
			_eligibleAtts.erase(std::remove(_eligibleAtts.begin(), _eligibleAtts.end(), _eligibleAtts[i]), _eligibleAtts.end());
			i--;
		}
		//filterEligibleRoutes(_eligibleAtts[i]->getDestination()->getCity());
	}

}

void TripService::filterEligibleRoutes(std::string city)
{
	for (TransportationRoute* t : _eligibleRoutes)
	{
		if (!(t->getDeparture() == city) && t->getDeparture()!="Anywhere")
		{
			if (!(t->getArrival() == city) && t->getArrival() != "Anywhere")
			{
				_eligibleRoutes.erase(std::remove(_eligibleRoutes.begin(), _eligibleRoutes.end(), t), _eligibleRoutes.end());
			}
		}
	}
}

bool TripService::hasAccinAttCity(const std::string& city)
{
	for (int i = 0; i < _eligibleAccs.size(); i++)
	{
		if (_eligibleAccs[i]->getDestination()->getCity() == city)
			return true;
	}
	return false;
}

std::vector<iAccommodation*> TripService::getAccForAtt(iAttraction* att)
{
	std::vector<iAccommodation*> accs;
	for (iAccommodation* acc : _eligibleAccs)
	{
		if (acc->getDestination()->getCity() == att->getDestination()->getCity())
		{
			accs.push_back(acc);
		}
	}
	return accs;
}

std::vector<TransportationRoute*> TripService::getTransportationBetweenCities(const std::string& departure, const std::string& arrival)
{
	std::vector<TransportationRoute*> routes;
	for (int i = 0; i < _eligibleRoutes.size(); i++)
	{
		if (_eligibleRoutes[i]->getDeparture() == departure)
		{
			if (_eligibleRoutes[i]->getArrival() == arrival)
			{
				routes.push_back(_eligibleRoutes[i]);
			}
		}
	}
	return routes;
}

TransportationRoute* TripService::getNoneTransportation()
{
	for (TransportationRoute* tr : _eligibleRoutes)
	{
		if (tr->getArrival() == "Anywhere")
		{
			if (tr->getDeparture() == "Anywhere")
			{
				return tr;
			}
		}
	}
	return nullptr;
}


TripService::TripService()
{
}

void TripService::assignNewEligibleAccommodations(std::vector<iAccommodation*>&& accs)
{
	_eligibleAccs = std::move(accs);
}

void TripService::assignNewEligibleAttractions(std::vector<iAttraction*>&& atts)
{
	_eligibleAtts = std::move(atts);
}

void TripService::assignNewEligibleRoutes(std::vector<TransportationRoute*>&& routes)
{
	_eligibleRoutes = std::move(routes);
}

Trip* TripService::buildTrip(const std::string& departureCity, int duration, const std::string& startingDate, const std::string& endingDate)
{
	Trip* trip = new Trip{};
	TransportationRepository repo;
	TransportationRoute* noneTransportation = getNoneTransportation();
	trip->setConfirmed(0);
	trip->setDuration(duration);
	trip->setStartDate(startingDate);
	trip->setEndDate(endingDate);
	//get cities that have both accs and attractions in it, considering the fact that routes exists everywhere
	filterLocations();
	std::string lastLocation;

	if (_eligibleAccs.size() == 0 || _eligibleAtts.size() == 0  || _eligibleRoutes.size()==0)
	{
		throw std::runtime_error{ "Nu se poate genera un traseu\n" };
	}
	for (int i = 0; i < duration; i++)
	{
		DayTrip* dt = new DayTrip{};

		int index = utils::chooseRandomNumber(_eligibleAtts.size());
		iAttraction* att = _eligibleAtts[index];

		std::vector<iAccommodation*> accs = getAccForAtt(att);
		iAccommodation* acc = accs[utils::chooseRandomNumber(accs.size())];
		if (accs.size() == 0)
		{
			throw std::runtime_error{ "Nu sunt destule cazari pentru generare trip\n" };
		}

		std::string departure;
		if (i == 0)
		{
			departure = departureCity;
		}
		else
		{
			departure = lastLocation;
		}
		std::string arrival = att->getDestination()->getCity();
		std::vector<TransportationRoute*> routes = getTransportationBetweenCities(departure, arrival);
		TransportationRoute* tr_route = nullptr;
		if (routes.size() == 0)
		{
			tr_route = noneTransportation;
		}
		else
		{
			tr_route = routes[utils::chooseRandomNumber(routes.size())];
		}
		dt->setAccommodation(acc);
		dt->setAttraction(att);
		dt->setRoute(tr_route);
		dt->setDayNumber(i + 1);
		trip->addDayTrip(i, dt);
		lastLocation = arrival;
	}

	trip->calculateTotalCost();
	return trip;
}

TripService::~TripService()
{
}

