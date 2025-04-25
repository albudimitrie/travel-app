#include "Destination.h"

void Destination::setId(int id) {
    _id = id;
}

void Destination::setName(const std::string& name) {
    _name = name;
}

void Destination::setCountry(const std::string& country) {
    _country = country;
}

void Destination::setCity(const std::string& city) {
    _city = city;
}

void Destination::setDescription(const std::string& description) {
    _description = description;
}

void Destination::setClimate(const std::string& climate) {
    _climate = climate;
}

void Destination::setIsActive(bool isActive) {
    _isActive = isActive;
}

int Destination::getId() const {
    return _id;
}

std::string Destination::getName() const {
    return _name;
}

std::string Destination::getCountry() const {
    return _country;
}

std::string Destination::getCity() const {
    return _city;
}

std::string Destination::getDescription() const {
    return _description;
}

std::string Destination::getClimate() const {
    return _climate;
}

bool Destination::isActive() const {
    return _isActive;
}