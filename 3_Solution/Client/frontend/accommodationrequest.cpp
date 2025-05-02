#include "accommodationrequest.h"

AccommodationRequest::AccommodationRequest(int id) {this->id=id;}

QByteArray AccommodationRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="GET_ACC_WITH_ID";
    jsonObj["id"]=id;

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
