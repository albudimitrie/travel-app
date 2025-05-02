#include "numberaccommodationsrequest.h"

NumberAccommodationsRequest::NumberAccommodationsRequest() {}

QByteArray NumberAccommodationsRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="GET_NUMBER_ALL_ACCOMMODATIONS";

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
