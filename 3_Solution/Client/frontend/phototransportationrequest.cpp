#include "phototransportationrequest.h"

PhotoTransportationRequest::PhotoTransportationRequest(int id) {this->id=id;}

QByteArray PhotoTransportationRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="GET_PHOTO_WITH_ID";
    jsonObj["type"]="transportation";
    jsonObj["id"]=id;

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
