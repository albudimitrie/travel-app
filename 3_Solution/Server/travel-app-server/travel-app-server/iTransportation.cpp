#include "iTransportation.h"
#include "PlaneTransport.h"
#include "Bus.h"
#include "TrainTransport.h"

iTransportation* FactoryTransportation::makePlaneTransport()
{
    return new PlaneTransport();
}

iTransportation* FactoryTransportation::makeTrainTransport()
{
    return new TrainTransport();
}

iTransportation* FactoryTransportation::makeBusTransportation()
{
    return new Bus();
}
