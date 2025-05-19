#pragma once
#include "iAttraction.h"
#include <string>


class Destination;
class AAttraction :    public iAttraction
{
protected:
	Destination* _destination;
	std::string _name;
	std::string _description;
	std::string _category;
	double _ticketPrice;

	int _id;
public:
    virtual ~AAttraction();

    void setDestination(Destination* destination);
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setTicketPrice(double price);
    void setId(int id);
    virtual void setCategory(const std::string& category) override;

    Destination* getDestination() const;
    std::string getName() const;
    std::string getDescription() const;
    std::string getCategory() const;
    double getTicketPrice() const;
    int getId() const;
};

