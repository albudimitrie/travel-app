#ifndef TRANSPORTATIONROUTE_H
#define TRANSPORTATIONROUTE_H

#include "transportation.h"

class TransportationRoute
{
private:
    int _id;
    QString _departure,
           _arrival;
    int _distance;
    int _duration;
    Transportation* _transport;
public:
    TransportationRoute(int id, QString departure, QString arrival, int distance, int duration, Transportation* transport);
    int getId() const { return _id; }
    QString getDeparture() const { return _departure; }
    QString getArrival() const { return _arrival; }
    int getDistance() const { return _distance; }
    int getDuration() const { return _duration; }
    Transportation* getTransport() const { return _transport; }

};

#endif // TRANSPORTATIONROUTE_H
