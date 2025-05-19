#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#undef UNICODE

#include "DataBaseCon.h"
#include "TCPServer.h"
#include <iostream>
#include <vector>
#include "Logger.h"
#include <vector>
#include "utils.h"

#include "DestinationRepository.h"
#include "AttractionRepository.h"
#include "TransportationRepository.h"
#include "TransportationRoute.h"
#include "iTransportation.h"
#include "iAttraction.h"
#include "Destination.h"
#include "iAccommodation.h"
#include "TransportationRoute.h"
#include "TripRepository.h"
#include "DayTrip.h"
#include "Trip.h"
#include "time.h"
#include "TripService.h"
#include "AccommodationRepository.h"
#include "AttractionRepository.h"
#include "TransportationRepository.h"

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
		AccommodationRepository repo_acc;
		AttractionRepository repo_att;
	/*	TransportationRepository repo_routes;
		std::vector<iAccommodation*> accs;
		for (int i = 1; i <= 8; i++)
		{
			accs.push_back(repo_acc.getAccWithID(i));
		}
		std::vector<iAttraction*> atts = repo_att.getAll();
		std::vector<TransportationRoute*> routes = repo_routes.getAllRoutes();

		TripService ts;
		ts.assignNewEligibleAccommodations(std::move(accs));
		ts.assignNewEligibleAttractions(std::move(atts));
		ts.assignNewEligibleRoutes(std::move(routes));*/

		//Trip* trip = ts.buildTrip("Suceava", 1, "", "");

		TCPServer server(12345);

		//TODO decomentare delete in TripRepo createTrip
		server.run();
		db->destroyInstance();
	}
	catch (std::exception &e)
	{
		std::cout << e.what()<<"\n";
	}

}