#include "TransportationRoute.h"
#include "iTransportation.h"


TransportationRoute::TransportationRoute()
{
}

int TransportationRoute::getId() const {
    return _id;
}

std::string TransportationRoute::getDeparture() const {
    return _departure;
}

std::string TransportationRoute::getArrival() const {
    return _arrival;
}

int TransportationRoute::getDistance() const {
    return _distance;
}

int TransportationRoute::getDuration() const {
    return _duration;
}

iTransportation* TransportationRoute::getTransport() const {
    return _transport;
}

void TransportationRoute::setId(int id) {
    _id = id;
}

void TransportationRoute::setDeparture(const std::string& departure) {
    _departure = departure;
}

void TransportationRoute::setArrival(const std::string& arrival) {
    _arrival = arrival;
}

void TransportationRoute::setDistance(int distance) {
    _distance = distance;
}

void TransportationRoute::setDuration(int duration) {
    _duration = duration;
}

void TransportationRoute::setTransport(iTransportation* transport) {
    _transport = transport;
}

TransportationRoute::~TransportationRoute()
{
    if (_transport)
    {
        delete _transport;
    }
}
