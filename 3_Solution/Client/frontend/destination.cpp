#include "destination.h"

Destination::Destination(int _id,QString _name,QString _country,QString _city,
                         QString _description,QString _climate,bool _isActive)
{
    this->_id=_id;
    this->_name=_name;
    this->_country=_country;
    this->_city=_city;
    this->_description=_description;
    this->_climate=_climate;
    this->_isActive=_isActive;
}
