#include "attraction.h"
#include"destination.h"

Attraction::Attraction(Destination*dest, QString name, QString description, QString category, double ticketPrice, int id)
{
    this->_destination=dest;
    this->_name=name;
    this->_category=category;
    this->_description=description;
    this->_ticketPrice=ticketPrice;
    this->_id=id;
}
