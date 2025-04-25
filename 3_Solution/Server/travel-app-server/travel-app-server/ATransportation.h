#pragma once
#include "iTransportation.h"
#include <string>
class ATransportation :    public iTransportation
{
protected:
	int _id;
	std::string _type,
				_company,
				_description;
	int _comfort_level,
		_capacity;
	double _averagePricePerTrip;
public:
    void setId(int id) override;
    void setCompany(const std::string& company) override;
    void setDescription(const std::string& description) override;
    void setComfortLevel(int level) override;
    void setCapacity(int capacity) override;
    void setAveragePricePerTrip(double price) override;

    int getId() const override;
    std::string getType() const override;
    std::string getCompany() const override;
    std::string getDescription() const override;
    int getComfortLevel() const override;
    int getCapacity() const override;
    double getAveragePricePerTrip() const override;
};

