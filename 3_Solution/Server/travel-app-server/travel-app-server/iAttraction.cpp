#include "iAttraction.h"
#include "CulturalAttraction.h"
#include "MusicalAttraction.h"
#include "ReligiousAttraction.h"

iAttraction* FactoryAttraction::makeReligiousAttraction()
{
    return new ReligiousAttraction();
}

iAttraction* FactoryAttraction::makeCulturalAttraction()
{
    return new CulturalAttraction();
}

iAttraction* FactoryAttraction::makeMusicalAttraction()
{
    return new MusicalAttraction();
}
