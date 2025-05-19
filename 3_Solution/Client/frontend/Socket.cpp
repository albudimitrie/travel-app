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
    // Initializare Winsock
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

    // Configurare adresa server
    clientService.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.1.1", &clientService.sin_addr.s_addr);
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

     //qDebug() << "Server JSON:" << jsonObj;

     qDebug()<<"Server: "<<buffer<<" .\n";

     return jsonObj;
}

QJsonObject Socket::receiveBigData(int size) {
    char* buffer = new char[size + 1];
    int total_received = 0;
    while (total_received < size) {
        int received_now = recv(client_sock, buffer + total_received, size - total_received, 0);
        if (received_now <= 0) {
            delete[] buffer;
            qDebug() << "Eroare la primirea pozei";
            return QJsonObject();  // returnezi obiect gol la eroare
        }
        total_received += received_now;
    }
    buffer[size] = '\0'; // s-ar putea sa nu fie pus /0 la final asa ca l fortez eu
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray(buffer, size));
    QJsonObject jsonObj = jsonDoc.object();
    //qDebug() << buffer;
    delete[] buffer;
    return jsonObj;
}
