#include "photoattractionrequest.h"

PhotoAttractionRequest::PhotoAttractionRequest(int id) {this->id=id;}

QByteArray PhotoAttractionRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="GET_PHOTO_WITH_ID";
    jsonObj["type"]="attraction";
    jsonObj["id"]=id;

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
