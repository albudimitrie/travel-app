#include "accommodation.h"
#include"destination.h"

Accommodation::Accommodation(int _id,QString _name,QString _type,QString _address,QString _description,
                            int _pricePerNight,QString _facilities,Destination*_destination)
{
    this->_id=_id;
    this->_name=_name;
    this->_type=_type;
    this->_address=_address;
    this->_description=_description;
    this->_facilities=_facilities;
    this->_pricePerNight=_pricePerNight;
    this->_destination=_destination;
}

void Accommodation::setBase64Data(QString data)
{
    this->base64photo=data;
}
