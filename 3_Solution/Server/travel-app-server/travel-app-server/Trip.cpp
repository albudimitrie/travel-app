#include "Trip.h"
#include "DayTrip.h"
#include <iostream>
#include "iAccommodation.h"
#include "iAttraction.h"
#include "TransportationRoute.h"
#include "iTransportation.h"
Trip::Trip()
{
	_totalCost = 0;
}

void Trip::setID(int id)
{
	_ID = id;
}

void Trip::setUserID(int id)
{
	_userID = id;
}

void Trip::setDuration(float duration)
{
	_duration = duration;
}

void Trip::setStartDate(std::string startDate)
{
	_startDate = startDate;
}

void Trip::setEndDate(std::string endDate)
{
	_endDate = endDate;
}

void Trip::setConfirmed(bool confirmed)
{
	_isConfirmed = confirmed;
}

void Trip::setTotalCost(float cost)
{
	_totalCost = cost;
}


float Trip::calculateTotalCost()
{
	_totalCost = 0;
	for (auto it = _organizareZile.begin(); it != _organizareZile.end(); it++)
	{
		iAccommodation* acc = it->second->getAccommodation();
		iAttraction* att = it->second->getAttraction();
		TransportationRoute* tr = it->second->getRoute();

		_totalCost += acc->getPricePerNight();
		_totalCost += att->getTicketPrice();
		_totalCost += tr->getDistance() * (tr->getTransport()->getAveragePricePerTrip());
	}
	
	return _totalCost;
}

int Trip::getID()const
{
	return _ID;
}

int Trip::getUserID()const
{
	return _userID;
}

float Trip::getDuration()const
{
	return _duration;
}

std::string Trip::getStartingDate()const
{
	return _startDate;
}

std::string Trip::getEndingDate()const
{
	return _endDate;
}

bool Trip::isConfirmed()const
{
	return _isConfirmed;
}

float Trip::getTotalCost()const
{
	return _totalCost;
}

std::map<int, DayTrip*> Trip::getDayTrips() const
{
	return _organizareZile;
}


void Trip::addDayTrip(int dayNumber, DayTrip* dt)
{
	if (dayNumber < 0 || dayNumber >= _duration)
	{
		throw std::runtime_error{ "Nu exista acest index pentru zi calatorie" };
	}
	_organizareZile[dayNumber] = dt;
}

Trip::~Trip()
{
	for (auto it = _organizareZile.begin(); it != _organizareZile.end(); it++)
	{
		delete it->second;
		it->second = nullptr;
	}
}
