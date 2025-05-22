#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE

#include "DataBaseCon.h"
#include "TCPServer.h"
#include <iostream>
#include "Logger.h"
#include "time.h"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

void main()
{
	try
	{
		srand(time(NULL));
		DataBaseCon* db = DataBaseCon::getInstance();
		db->connect("ALBUU\\SQLEXPRESS", "TravelApp");
		Logger::getInstance()->setPath("LOGS.txt");
		TCPServer server(12345);
		server.run();
		server.cleanup();
		db->destroyInstance();
	}
	catch (std::exception &e)
	{
		std::cout << e.what()<<"\n";
	}

}