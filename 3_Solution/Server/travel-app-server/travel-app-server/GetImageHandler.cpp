
#include "GetImageHandler.h"
#include "include\json.hpp"
#include "AccommodationRepository.h"
#include "AttractionRepository.h"
#include "TransportationRepository.h"        
#include "utils.h"
#include <stdio.h>

using json = nlohmann::json;

GetImageHandler::GetImageHandler(TCPServer& server)
	:_server{server}
{
	this->_reqType = "GET_PHOTO_WITH_ID";
}

nlohmann::json GetImageHandler::handle(nlohmann::json& request)
{
    json reply;
    std::string path;
    if (request["type"] == "accommodation")
    {
        AccommodationRepository repo;
        path = repo.getPhotoPathOnID(request["id"]);
    }
    else if (request["type"] == "attraction")
    {
        AttractionRepository repo;
        path = repo.getPhotoWithID(request["id"]);
    }
    else if (request["type"] == "transportation")
    {
        TransportationRepository repo;
        path = repo.getPhotoWithID(request["id"]);

    }
    FILE* file = fopen(path.c_str(), "rb");
    if (!file)
    {
        throw std::runtime_error{ "Nu exista path pentru aceasta imagine" };
    }

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    int dimensiune = utils::base64EncodedSize(size);
    json size_json;

    unsigned char* buffer = new unsigned char[size + 1];
    memset(buffer, 0, size + 1);
    fread(buffer, sizeof(unsigned char), size, file);

    reply["encoded"] = utils::base64encode(buffer, size);

    std::string str_reply = reply.dump();
    int dim_frame = str_reply.size();

    int photo_size = std::string(reply["encoded"]).size();

    size_json["size"] = dim_frame;
    size_json["photo_size"] = photo_size;
    //std::cout << dim_frame << " frame size\t" << photo_size << " : photo size\n";     //for debug

    std::string size_json_str = size_json.dump();

    _server.send_data(size_json_str.c_str());
    _server.send_data(str_reply.c_str());
    fclose(file);
    delete[] buffer;
    buffer = nullptr;

	json reply2; //nu trimit nimic in functia serverului, deja o sa efectuez de aici niste senduri
	return reply2;
}
