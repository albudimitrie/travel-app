#include "transportationroute.h"

TransportationRoute::TransportationRoute(int id, QString departure, QString arrival, int distance,
                                         int duration, Transportation* transport)
{
    this->_id=id;
    this->_departure=departure;
    this->_arrival=arrival;
    this->_distance=distance;
    this->_duration=duration;
    this->_transport=transport;
}
