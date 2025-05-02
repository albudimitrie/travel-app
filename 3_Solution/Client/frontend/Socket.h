#ifndef SOCKET_H
#define SOCKET_H

#undef UNICODE
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <QJsonDocument>
#include <QJsonObject>


class Socket {
private:
    WSADATA wsaData;
    SOCKET client_sock;
    struct sockaddr_in clientService;
    static Socket*instance;
    Socket();
    ~Socket();

public:
    static Socket* getInstance();
    void sendMessage(const char* message);
    QJsonObject receiveMessage();
    QJsonObject receivePhoto(int size);
};

#endif // SOCKET_H
