#include "registerrequest.h"

RegisterRequest::RegisterRequest(QString username,QString password) {
    this->username=username;
    this->password=password;
}

QByteArray RegisterRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="REGISTER";
    jsonObj["username"] = username;
    jsonObj["password"] = password;

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
