#pragma once
#include <string>

class iTransportation
{
public:
    virtual void setId(int id) = 0;
    virtual void setCompany(const std::string& company) = 0;
    virtual void setDescription(const std::string& description) = 0;
    virtual void setComfortLevel(std::string level) = 0;
    virtual void setCapacity(int capacity) = 0;
    virtual void setAveragePricePerTrip(double price) = 0;

    virtual int getId() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getCompany() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::string getComfortLevel() const = 0;
    virtual int getCapacity() const = 0;
    virtual double getAveragePricePerTrip() const = 0;

    virtual ~iTransportation() = default;
};



class FactoryTransportation
{
public:
    static iTransportation* makePlaneTransport();
    static iTransportation* makeTrainTransport();
    static iTransportation* makeBusTransportation();
};
