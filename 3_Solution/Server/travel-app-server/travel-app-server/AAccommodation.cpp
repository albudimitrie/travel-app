#include "AAccommodation.h"

void AAccommodation::setId(int id)
{
	_id = id;
}


void AAccommodation::setName(const std::string& name)
{
	_name = name;
}

void AAccommodation::setAddress(const std::string& address)
{
	_address = address;
}

void AAccommodation::setDescription(const std::string& description)
{
	_description = description;
}

void AAccommodation::setFacilities(const std::string& facilities)
{
	_facilities = facilities;
}


void AAccommodation::clearFacilities()
{
	_facilities.clear();
}

void AAccommodation::setPricePerNight(int price)
{
	_pricePerNight = price;
}

Destination* AAccommodation::getDestination() const
{
	return _destination;
}
