#include "iAccommodation.h"
#include "Hotel.h"
#include "Apartament.h"
#include "Pensiune.h"

iAccommodation* FactoryAccommodations::makeHotel()
{
	return new Hotel();
}

iAccommodation* FactoryAccommodations::makePensiune()
{
	return new Pensiune();
}

iAccommodation* FactoryAccommodations::makeApartament()
{
	return new Apartament();
}
