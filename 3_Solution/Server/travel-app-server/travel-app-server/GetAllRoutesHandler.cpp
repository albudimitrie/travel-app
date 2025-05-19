#include "TCPServer.h"
#include "GetAllRoutesHandler.h"
#include "include/json.hpp"
#include "TransportationRepository.h"
#include "iTransportation.h"
#include "TransportationRoute.h"



using json = nlohmann::json;

GetAllRoutesHandler::GetAllRoutesHandler(TCPServer& server)
	:_server{server}
{
	_reqType = "GET_ALL_ROUTES";
}

nlohmann::json GetAllRoutesHandler::handle(nlohmann::json& request)
{

    TransportationRepository repo;
    std::vector<TransportationRoute *> rute = repo.getAllRoutes();

    json j_transportations;
    j_transportations["routes"] = json::array();
    for (int i = 0; i < rute.size(); i++) {
        json tr_obj;
        tr_obj["RouteID"] = rute[i]->getId();
        tr_obj["CityDeparture"] = rute[i]->getDeparture();
        tr_obj["CityArrival"] = rute[i]->getArrival();
        tr_obj["Distance"] = rute[i]->getDistance();
        tr_obj["Duration"] = rute[i]->getDuration();

        iTransportation* tr = rute[i]->getTransport();
        tr_obj["TransportationID"] = tr->getId();
        tr_obj["Type"] = tr->getType();
        tr_obj["Company"] = tr->getCompany();
        tr_obj["Description"] = tr->getDescription();
        tr_obj["PricePerKm"] = tr->getAveragePricePerTrip();
        tr_obj["Capacity"] = tr->getCapacity();
        tr_obj["ComfortLevel"] = tr->getComfortLevel();

        j_transportations["routes"].push_back(tr_obj);
    }
    std::string tr_string = j_transportations.dump();
    //std::cout << tr_string << "\n";


    json j_size_tr;
    j_size_tr["size"] = tr_string.size();

    std::string str_size_tr = j_size_tr.dump();

    _server.send_data(str_size_tr.c_str()); //trimit size pachet
    _server.send_data(tr_string.c_str());  //trimit pachet

    for (TransportationRoute* tr : rute)
    {
        if (tr)
        {
            delete tr;
        }
    }
    return json();

}
