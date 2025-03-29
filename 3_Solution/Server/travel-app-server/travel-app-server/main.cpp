#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE



#include "DataBaseCon.h"
#include "TCPServer.h"
#include <iostream>
#include <vector>
#include "include\json.hpp"

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


using json = nlohmann::json;

void main()
{
	try
	{
	DataBaseCon* db = DataBaseCon::getInstance();
			if (db->connect("ALBUU\\SQLEXPRESS", "TravelApp"))
		{
			/*std::vector<std::vector<std::string>> results;
			db->executeQuery("SELECT * FROM Users", results);
			for (int i = 0; i < results.size(); i++)
			{
				for (int j = 0; j < 3; j++)
				{
					std::cout << results[i][j] << " ";
				}
				std::cout << "\n";
			}*/
		}



		TCPServer server(12345);
		server.run();
		

	}
	catch (...)
	{



		std::cout << "Eroare\n";
	}




}