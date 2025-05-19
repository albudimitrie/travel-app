#undef UNICODE
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include "include\json.hpp"
#include "HandlerManager.h"
#include "iHandler.h"
#include "Logger.h"

using json = nlohmann::json;

class TCPServer {
private:
    WSADATA wsaData;
    SOCKET listen_sock;
    SOCKET client_sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int port;
    bool initialized;
    char recv_buffer[1024];

public:
    TCPServer(int port);

    ~TCPServer();
    bool initialize();
    bool start_listening();
    bool accept_connection();
    std::string receive_data();
    bool send_data(const char* data);
    void cleanup();
    void run();
};
