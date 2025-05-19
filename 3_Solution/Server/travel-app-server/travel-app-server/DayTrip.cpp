#include "DayTrip.h"
#include "iAccommodation.h"
#include "iAttraction.h"
#include "TransportationRoute.h"

void DayTrip::setID(int id)
{
	_ID = id;
}

void DayTrip::setTripID(int id)
{
	_tripID = id;
}

void DayTrip::setDayNumber(int number)
{
	_dayNumber = number;
}

void DayTrip::setAccommodation(iAccommodation* acc)
{
	_acc = acc;
}

void DayTrip::setAttraction(iAttraction* attr)
{
	_attr = attr;
}

void DayTrip::setRoute(TransportationRoute* route)
{
	_route = route;
}

int DayTrip::getID()const
{
	return _ID;
}

int DayTrip::getTripID()const
{
	return _tripID;
}

int DayTrip::getDayNumber()const
{
	return _dayNumber;
}

iAccommodation* DayTrip::getAccommodation()const
{
	return _acc;
}

iAttraction* DayTrip::getAttraction()const
{
	return _attr;
}

TransportationRoute* DayTrip::getRoute()const
{
	return _route;
}

DayTrip::DayTrip()
{
	if (_acc)
	{
		delete _acc;
	}
	if (_attr)
	{
		delete _attr;
	}
	if (_route)
	{
		delete _route;
	}
}
