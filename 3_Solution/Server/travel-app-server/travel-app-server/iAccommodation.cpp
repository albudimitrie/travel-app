#include "iAccommodation.h"

iAccommodation* FactoryAccommodations::makeHotel(int id, int destinationId, std::string name, std::string address, std::string description, std::list<std::string>& facilities, int pricePerNight)
{
	return nullptr;
}

iAccommodation* FactoryAccommodations::makePensiune(int id, int destinationId, std::string name, std::string address, std::string description, std::list<std::string>& facilities, int pricePerNight)
{
	return nullptr;
}

iAccommodation* FactoryAccommodations::makeApartament(int id, int destinationId, std::string name, std::string address, std::string description, std::list<std::string>& facilities, int pricePerNight)
{
	return nullptr;
}
