#include "ATransportation.h"
void ATransportation::setId(int id) {
    _id = id;
}


void ATransportation::setCompany(const std::string& company) {
    _company = company;
}

void ATransportation::setDescription(const std::string& description) {
    _description = description;
}

void ATransportation::setComfortLevel(int level) {
    _comfort_level = level;
}

void ATransportation::setCapacity(int capacity) {
    _capacity = capacity;
}

void ATransportation::setAveragePricePerTrip(double price) {
    _averagePricePerTrip = price;
}

int ATransportation::getId() const {
    return _id;
}

std::string ATransportation::getType() const {
    return _type;
}

std::string ATransportation::getCompany() const {
    return _company;
}

std::string ATransportation::getDescription() const {
    return _description;
}

int ATransportation::getComfortLevel() const {
    return _comfort_level;
}

int ATransportation::getCapacity() const {
    return _capacity;
}

double ATransportation::getAveragePricePerTrip() const {
    return _averagePricePerTrip;
}