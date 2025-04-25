#pragma once
#include "iAccommodation.h"
#include <string>
#include <list>
class Destination;
class AAccommodation : public iAccommodation
{
protected:
	int _id;
	std::string _name,
		_type,
		_address,
		_description;
    std::string _facilities;
	int _pricePerNight;
	Destination* _destination;
public:
	virtual void setId(int id) override;
	virtual void setName(const std::string& name) override;
	virtual void setAddress(const std::string& address) override;
	virtual void setDescription(const std::string& description) override;
	virtual void setFacilities(const std::string& facilities) override;
	virtual void clearFacilities() override;
	virtual void setPricePerNight(int price) override;


	virtual int getID() const override { return _id; }
	virtual std::string getName() const override { return _name; }
	virtual std::string getType() const override { return _type; }
	virtual Destination* getDestination()const override;
	virtual std::string getDescription() const override { return _description; };
	virtual std::string getFacilities() const { return _facilities; };
	virtual int getPricePerNight() const override { return _pricePerNight; }
	virtual ~AAccommodation() = default;


};

