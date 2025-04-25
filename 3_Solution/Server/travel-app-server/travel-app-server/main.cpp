#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE



#include "DataBaseCon.h"
#include "TCPServer.h"
#include <iostream>
#include <vector>
#include "include\json.hpp"
#include "Logger.h"
#include "UserRepository.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


using json = nlohmann::json;

void main()
{
	try
	{
	DataBaseCon* db = DataBaseCon::getInstance();
	db->connect("ALBUU\\SQLEXPRESS", "TravelApp");
	Logger::getInstance()->setPath("LOGS.txt");
	UserRepository users;
	TCPServer server(12345);
	server.run();
	}
	catch (...)
	{
		std::cout << "Eroare\n";
	}
}