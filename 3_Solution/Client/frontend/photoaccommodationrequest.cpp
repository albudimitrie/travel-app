#include "photoaccommodationrequest.h"

PhotoAccommodationRequest::PhotoAccommodationRequest(int id) {this->id=id;}

QByteArray PhotoAccommodationRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="GET_PHOTO_WITH_ID";
    jsonObj["type"]="accommodation";
    jsonObj["id"]=id;

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
