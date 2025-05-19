#pragma once
#include <vector>
#include <string>
#include <time.h>
#include "utils.h"


class iAccommodation;
class iAttraction;
class TransportationRoute;
class iTransportation;

class DayTrip;
class Trip;

//o calatorie va putea fi realizata intr o singura tara

class TripService
{
	std::vector<iAccommodation*> _eligibleAccs;
	std::vector<iAttraction*> _eligibleAtts;
	std::vector<TransportationRoute*> _eligibleRoutes;
	void filterLocations();
	void filterEligibleRoutes(std::string city);
	bool hasAccinAttCity(const std::string& city);
	std::vector<iAccommodation*>getAccForAtt(iAttraction* att);
	std::vector<TransportationRoute*> getTransportationBetweenCities(const std::string& departure, const std::string& arrival);
	TransportationRoute* getNoneTransportation();

public:
	TripService();
	void assignNewEligibleAccommodations(std::vector<iAccommodation*>&& accs);
	void assignNewEligibleAttractions(std::vector<iAttraction*>&& atts);
	void assignNewEligibleRoutes(std::vector<TransportationRoute*>&& routes);

	Trip* buildTrip(const std::string& departureCity, int duration, const std::string &startingDate, const std::string &endingDate);
	~TripService();

};

