#pragma once
#include <string>
#include <list>

class Destination;

class iAccommodation
{
public:
	//-------------------------------------------------------------------------------------------------------------
	virtual void setId(int id) = 0;
	virtual void setDestination(Destination* dest) = 0;
	virtual void setName(const std::string& name) = 0;
	virtual void setAddress(const std::string& address) = 0;
	virtual void setDescription(const std::string& description) = 0;
	virtual void setFacilities(const std::string& facilities) = 0;
	virtual void clearFacilities() = 0;
	virtual void setPricePerNight(int price) = 0;

	//-------------------------------------------------------------------------------------------------------------
	virtual int getID() const = 0;
	virtual std::string getName() const = 0;
	virtual std::string getType() const = 0;
	virtual std::string getAddress() const = 0;
	virtual Destination* getDestination() const = 0;
	virtual std::string getDescription() const = 0;
	virtual std::string getFacilities() const = 0;
	virtual int getPricePerNight() const = 0;
	virtual ~iAccommodation() = default;
	
};


class FactoryAccommodations
{
public:
	static iAccommodation* makeHotel();
	static iAccommodation* makePensiune();
	static iAccommodation* makeApartament();
};
