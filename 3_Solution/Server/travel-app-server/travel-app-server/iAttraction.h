#pragma once
#include <string>

class Destination;

class iAttraction
{
public:
    virtual void setDestination(Destination* destination) = 0;
    virtual void setName(const std::string& name) = 0;
    virtual void setDescription(const std::string& description) = 0;
    virtual void setCategory(const std::string& category) = 0;
    virtual void setTicketPrice(double price) = 0;
    virtual void setId(int id) = 0;

    virtual Destination* getDestination() const = 0;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getCategory() const = 0;
    virtual double getTicketPrice() const = 0;
    virtual int getId() const = 0;
};


class FactoryAttraction
{
public:
    static iAttraction* makeReligiousAttraction();
    static iAttraction* makeCulturalAttraction();
    static iAttraction* makeMusicalAttraction();
};
