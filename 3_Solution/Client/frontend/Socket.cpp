#include "Socket.h"
#include <iostream>
#include <QDebug>

Socket* Socket::instance=nullptr;

Socket* Socket::getInstance()
{
    if(instance==nullptr)instance = new Socket();
    return instance;
}
Socket::Socket() {
    // Inițializare Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        qDebug()<<"WSAStartup failed!\n";
        return;
    }

    // Creare socket
    client_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_sock == INVALID_SOCKET) {
         qDebug()<<"Socket creation failed: %d\n", WSAGetLastError();
        WSACleanup();
        return;
    }

    // Configurare adresă server
    clientService.sin_family = AF_INET;
    inet_pton(AF_INET, "25.31.220.17", &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(12345);

    // Conectare la server
    if (connect(client_sock, (struct sockaddr*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
         qDebug()<<"Connection failed: %d\n", WSAGetLastError();
        closesocket(client_sock);
        WSACleanup();
        return;
    }

    qDebug() << "Connected to server!\n";
}

Socket::~Socket() {
    closesocket(client_sock);
    WSACleanup();
    qDebug()<<"Socket closed.\n";
}

void Socket::sendMessage(const char* message) {
    send(client_sock, message, strlen(message) + 1, 0);
}

QJsonObject Socket::receiveMessage() {
     char buffer[1024] = {0};
     recv(client_sock, buffer, 1024, 0);

     QJsonDocument jsonDoc = QJsonDocument::fromJson(buffer);

     QJsonObject jsonObj = jsonDoc.object();

     qDebug() << "Server JSON:" << jsonObj;

     qDebug()<<"Server: "<<buffer<<" .\n";

     return jsonObj;


}
