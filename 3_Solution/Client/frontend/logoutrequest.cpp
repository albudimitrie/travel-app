#include "logoutrequest.h"


LogoutRequest::LogoutRequest(QString username)
{
    this->username=username;
}

QByteArray LogoutRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="LOG_OUT";
    jsonObj["username"] = username;

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
