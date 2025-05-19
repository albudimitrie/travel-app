#include "transportation.h"

Transportation::Transportation(int id, QString type, QString company, QString description, QString comfort_level ,
                               int capacity, double averagePricePerTrip )
{
    this->_id=id;
    this->_type=type;
    this->_company=company;
    this->_description=description;
    this->_comfort_level=comfort_level;
    this->_capacity=capacity;
    this->_averagePricePerTrip=averagePricePerTrip;
}
