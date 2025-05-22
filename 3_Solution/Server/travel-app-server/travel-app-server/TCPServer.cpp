#include "TCPServer.h"

TCPServer::TCPServer(int port)
{
    this->port = port;
    this->initialized = false;
    this->listen_sock = INVALID_SOCKET;
    this->client_sock = INVALID_SOCKET;
    ZeroMemory(recv_buffer, sizeof(recv_buffer));
}

TCPServer::~TCPServer()
{
    cleanup();
}

bool TCPServer::initialize()
{
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        printf("WSAStartup failed with error: %d\n", result);
        Logger::getInstance()->logSockActions(LogStatus::ERROR_, "WSAStartup failed");
        return false;
    }

    listen_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_sock == INVALID_SOCKET) {
        printf("socket function failed with error: %ld\n", WSAGetLastError());
        Logger::getInstance()->logSockActions(LogStatus::ERROR_, "socket function failed");
        WSACleanup();
        return false;
    }

    ZeroMemory(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    result = bind(listen_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (result == SOCKET_ERROR) {
        printf("bind function failed with error: %d\n", WSAGetLastError());
        Logger::getInstance()->logSockActions(LogStatus::ERROR_, "bind function failed");
        closesocket(listen_sock);
        WSACleanup();
        return false;
    }

    initialized = true;
    Logger::getInstance()->logSockActions(LogStatus::SUCCES, "Server initialized succesfully...");
    return true;
}

bool TCPServer::start_listening()
{
    if (!initialized && !initialize()) {
        return false;
    }

    if (listen(listen_sock, SOMAXCONN) == SOCKET_ERROR) {
        printf("listen function failed with error: %d\n", WSAGetLastError());
        closesocket(listen_sock);
        WSACleanup();
        return false;
    }

    printf("Server is listening on port %d...\n", port);
    return true;
}

bool TCPServer::accept_connection()
{
    int client_addr_size = sizeof(client_addr);
    client_sock = accept(listen_sock, (struct sockaddr*)&client_addr, &client_addr_size);

    if (client_sock == INVALID_SOCKET) {
        printf("accept function failed with error: %ld\n", WSAGetLastError());
        Logger::getInstance()->logSockActions(LogStatus::ERROR_, "Accept function failed");
        return false;
    }

    char client_ip[46];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
    printf("Client connected: %s\n", client_ip);
    Logger::getInstance()->logSockActions(LogStatus::STATUS::SUCCES, "Client connected");

    return true;
}
std::string TCPServer::receive_data()
{
    if (client_sock == INVALID_SOCKET) {
        return "";
    }

    ZeroMemory(recv_buffer, sizeof(recv_buffer));
    int bytes_received = recv(client_sock, recv_buffer, sizeof(recv_buffer) - 1, 0);

    if (bytes_received > 0) {
        recv_buffer[bytes_received] = '\0';
        //printf("Received: %s\n", recv_buffer);
        return std::string(recv_buffer);
    }
    else if (bytes_received == 0) {
        printf("Connection closed by client\n");
        Logger::getInstance()->logSockActions(LogStatus::STATUS::SUCCES, "Connection closed by client");
        return "";
    }
    else {
        printf("Client closed connection abruptely\n");
        return "";
    }
}

bool TCPServer::send_data(const char* data)
{
    if (client_sock == INVALID_SOCKET) {
        return false;
    }

    int bytes_sent = send(client_sock, data, (int)strlen(data), 0);
    if (bytes_sent == SOCKET_ERROR) {
        printf("send failed with error: %d\n", WSAGetLastError());
        return false;
    }
    bool ok = 0;
    do
    {
        std::string received = receive_data();
        if (received.empty())
        {
            return false;
        }
        json j_received = json::parse(received);
        if (j_received["action"] == "ACK")
        {
            ok = true;
        }
        else
        {
            ok = false;
        }

    } while (!ok);
    return true;
}

void TCPServer::cleanup()
{
    if (client_sock != INVALID_SOCKET) {
        closesocket(client_sock);
        client_sock = INVALID_SOCKET;
    }

    if (listen_sock != INVALID_SOCKET) {
        closesocket(listen_sock);
        listen_sock = INVALID_SOCKET;
    }

    if (initialized) {
        WSACleanup();
        initialized = false;
    }
}

void TCPServer::run()
{
    HandlerManager handlers;
    handlers.addHandler(FactoryHandlers::makeLoginHandler());
    handlers.addHandler(FactoryHandlers::makeRegisterHandler());
    handlers.addHandler(FactoryHandlers::makeLogoutHandler());
    handlers.addHandler(FactoryHandlers::makeGetSearchHistoryHandler());
    handlers.addHandler(FactoryHandlers::makeGetNumberAccommodations());
    handlers.addHandler(FactoryHandlers::makeGetAccWithId());
    handlers.addHandler(FactoryHandlers::makeGetPhoto(*this));
    handlers.addHandler(FactoryHandlers::makeGetAllAttractions(*this));
    handlers.addHandler(FactoryHandlers::makeGetAllRoutesHandler(*this));
    handlers.addHandler(FactoryHandlers::makeAddCustomTripHandler());
    handlers.addHandler(FactoryHandlers::makeGetTripHistoryHandler(*this));
    handlers.addHandler(FactoryHandlers::makeTripConfirmationHandler());
    handlers.addHandler(FactoryHandlers::makeGenerateTripHandler(*this));
    handlers.addHandler(FactoryHandlers::makeConfirmationOfGeneratedTrips());
    handlers.addHandler(FactoryHandlers::makeAddNewSearchHandler());

    if (!start_listening()) {
        return;
    }
    while (true)
    {
        if (accept_connection()) {
            while (true) {
                std::string received = receive_data();
                if (received.empty()) {
                    printf("Client disconnected. Waiting for a new connection...\n");
                    Logger::getInstance()->logSockActions(LogStatus::SUCCES, "Client disconnected.Waiting for a new connection...");
                    closesocket(client_sock);
                    client_sock = INVALID_SOCKET;
                    break;
                }
                json j_received = json::parse(received);
                json reply = handlers.processRequest(j_received);
                std::string str_reply = reply.dump();
                if (!reply.empty()) {
                    if (!send_data(str_reply.c_str()))
                    {
                        break;
                    }
                }
            }
        }
    }
}
