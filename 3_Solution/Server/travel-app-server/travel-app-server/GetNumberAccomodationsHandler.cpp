#include "GetNumberAccomodationsHandler.h"
#include "include/json.hpp"
#include "AccommodationRepository.h"
using json = nlohmann::json;

GetNumberAccomodationsHandler::GetNumberAccomodationsHandler()
{
    this->_reqType = "GET_NUMBER_ALL_ACCOMMODATIONS";
}

nlohmann::json GetNumberAccomodationsHandler::handle(nlohmann::json& request)
{
    AccommodationRepository aco;
    json reply;
    std::vector<int > ids = aco.getIDS();
    reply["size"] = ids.size();
    reply["values"] = ids;
    return reply;
}
