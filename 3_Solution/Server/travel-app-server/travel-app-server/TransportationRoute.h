#pragma once
#include <string>

class iTransportation;
class TransportationRoute
{
	int _id;
	std::string _departure,
				_arrival;
	int _distance,
		_duration;
	iTransportation* _transport;
public:
	TransportationRoute();

    int getId() const;
    std::string getDeparture() const;
    std::string getArrival() const;
    int getDistance() const;
    int getDuration() const;
    iTransportation* getTransport() const;

    void setId(int id);
    void setDeparture(const std::string& departure);
    void setArrival(const std::string& arrival);
    void setDistance(int distance);
    void setDuration(int duration);
    void setTransport(iTransportation* transport);
    ~TransportationRoute();
};

