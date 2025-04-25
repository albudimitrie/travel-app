#include "AAttraction.h"

void AAttraction::setDestination(Destination* destination) {
    _destination = destination;
}

void AAttraction::setName(const std::string& name) {
    _name = name;
}

void AAttraction::setDescription(const std::string& description) {
    _description = description;
}

void AAttraction::setTicketPrice(double price) {
    _ticketPrice = price;
}

void AAttraction::setId(int id) {
    _id = id;
}

Destination* AAttraction::getDestination() const {
    return _destination;
}

std::string AAttraction::getName() const {
    return _name;
}

std::string AAttraction::getDescription() const {
    return _description;
}

std::string AAttraction::getCategory() const {
    return _category;
}

double AAttraction::getTicketPrice() const {
    return _ticketPrice;
}

int AAttraction::getId() const {
    return _id;
}