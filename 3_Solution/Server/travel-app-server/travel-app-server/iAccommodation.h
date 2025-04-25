#pragma once
#include <string>
#include <list>

class Destination;

class iAccommodation
{
public:
	virtual void setId(int id) = 0;
	virtual void setDestinationID(int destinationID) = 0;
	virtual void setName(const std::string& name) = 0;
	virtual void setAddress(const std::string& address) = 0;
	virtual void setDescription(const std::string& description) = 0;
	virtual void setFacilities(const std::string& facilities) = 0;
	virtual void clearFacilities() = 0;
	virtual void setPricePerNight(int price) = 0;


	virtual int getID() const = 0;
	virtual int getDestID() const = 0;
	virtual std::string getName() const = 0;
	virtual std::string getType() const = 0;
	virtual std::string getCity() const = 0;
	virtual std::string getCountry() const = 0;
	virtual Destination* getDestination() const = 0;
	virtual std::string getDescription() const = 0;
	virtual std::string getFacilities() const = 0;
	virtual int getPricePerNight() const = 0;
	virtual ~iAccommodation() = default;
	
};
class FactoryAccommodations
{
public:
	static iAccommodation* makeHotel(int id, int destinationId, std::string name, std::string address, std::string description,
									 std::list<std::string > &facilities,
									 int pricePerNight);
	static iAccommodation* makePensiune(int id, int destinationId, std::string name, std::string address, std::string description,
									    std::list<std::string >& facilities,
										int pricePerNight);
	static iAccommodation* makeApartament(int id, int destinationId, std::string name, std::string address, std::string description,
										  std::list<std::string >& facilities,
									      int pricePerNight);
};
