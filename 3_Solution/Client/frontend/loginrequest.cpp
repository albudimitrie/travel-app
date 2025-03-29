#include "loginrequest.h"
#include <QJsonDocument>
#include <QJsonObject>

LoginRequest::LoginRequest(QString username,QString password) {
    this->username=username;
    this->password=password;
}

QByteArray LoginRequest::getRequest()
{
    QJsonObject jsonObj;
    jsonObj["action"]="LOG_IN";
    jsonObj["username"] = username;
    jsonObj["password"] = password;

    QJsonDocument jsonDoc(jsonObj);

    QByteArray jsonData = jsonDoc.toJson();

    return jsonData;
}
