#include "GetAllAttractionsHandler.h"
#include "include/json.hpp"
#include "TCPServer.h"
#include "AttractionRepository.h"
#include "iAttraction.h"
#include "Destination.h"

using json = nlohmann::json;

GetAllAttractionsHandler::GetAllAttractionsHandler(TCPServer& server)
	:_server{server}
{
	this->_reqType = "GET_ALL_ATTRACTIONS";
}

nlohmann::json GetAllAttractionsHandler::handle(nlohmann::json& request)
{
	AttractionRepository repo;
	std::vector<iAttraction*> attractions = repo.getAll();

    json j_attractions;
    j_attractions["attractions"] = json::array();
    for (int i = 0; i < attractions.size(); i++) {
        json attraction_obj;
        attraction_obj["AttractionID"] = attractions[i]->getId();
        attraction_obj["Name"] = attractions[i]->getName();
        attraction_obj["Description"] = attractions[i]->getDescription();
        attraction_obj["Category"] = attractions[i]->getCategory();
        attraction_obj["TicketPrice"] = attractions[i]->getTicketPrice();

        Destination* dest = attractions[i]->getDestination();
        attraction_obj["DestinationID"] = dest->getId();
        attraction_obj["DestinationName"] = dest->getName();
        attraction_obj["Country"] = dest->getCountry();
        attraction_obj["City"] = dest->getCity();
        attraction_obj["DestinationDescription"] = dest->getDescription();
        attraction_obj["Climate"] = dest->getClimate();

        j_attractions["attractions"].push_back(attraction_obj);
    }
    std::string attr_string = j_attractions.dump();


    json j_size_att;
    j_size_att["size"] = attr_string.size();

    std::string str_size_att = j_size_att.dump();

    _server.send_data(str_size_att.c_str()); //trimit size pachet
    _server.send_data(attr_string.c_str());  //trimit pachet

    for (iAttraction* at : attractions)
    {
        if (at)
        {
            delete at;
        }
    }

	return nlohmann::json(); //returnez json gol ca sa nu fie acesta trimis
}
