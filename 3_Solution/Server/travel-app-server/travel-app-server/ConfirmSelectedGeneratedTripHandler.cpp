#include "ConfirmSelectedGeneratedTripHandler.h"
#include "include/json.hpp"
#include "TripRepository.h"

ConfirmSelectedGeneratedTripHandler::ConfirmSelectedGeneratedTripHandler()
{
	this->_reqType = "CONFIRM_SELECTED_GENERATED_TRIP";

}

nlohmann::json ConfirmSelectedGeneratedTripHandler::handle(nlohmann::json& request)
{
	try
	{
		TripRepository repo;
		int id = request["tripID"];
		repo.moveGeneratedTripToPermanentTripHistory(id);

	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
	}


	return nlohmann::json();
}
