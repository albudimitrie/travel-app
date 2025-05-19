#pragma once

class iAccommodation;
class iAttraction;
class TransportationRoute;

class DayTrip
{
	int	_ID,
		_tripID,
		_dayNumber;
	iAccommodation* _acc;
	iAttraction* _attr;
	TransportationRoute* _route;

public:
	//----------------------------------------------SETTERS---------------------------------------------------------------
	void setID(int id);
	void setTripID(int id);
	void setDayNumber(int number);
	void setAccommodation(iAccommodation* acc);
	void setAttraction(iAttraction* attr);
	void setRoute(TransportationRoute* route);

	//-----------------------------------------------GETTERS--------------------------------------------------------------
	int getID()const;
	int getTripID()const;
	int getDayNumber()const;
	iAccommodation* getAccommodation()const;
	iAttraction* getAttraction()const;
	TransportationRoute* getRoute()const;
	DayTrip();
};

