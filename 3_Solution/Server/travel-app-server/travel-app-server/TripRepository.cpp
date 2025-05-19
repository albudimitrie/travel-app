#include "TripRepository.h"
#include "DayTrip.h"
#include "iAccommodation.h"
#include "iAttraction.h"
#include "TransportationRoute.h"
#include <iostream>

void TripRepository::create(const Trip& obj)
{
    std::string id, duration, isConfirmed, totalCost;
    id = std::to_string(obj.getUserID());
    duration = std::to_string(obj.getDuration());
    isConfirmed = std::to_string(obj.isConfirmed());
    totalCost = std::to_string(obj.getTotalCost());

	std::string query = "EXEC CreateTrip " + id + ", '" + obj.getStartingDate()+"','" + obj.getEndingDate() +"', " + duration +", " + isConfirmed +", " + totalCost+";";
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement exec CreateTrip");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare inserare Trip");
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Inserted new trip");

    try
    {
        int tripID = getIdForLastInsertedTrip();
        std::map<int, DayTrip*> organizare = obj.getDayTrips();
        for (auto it = organizare.begin(); it != organizare.end(); it++)
        {
            it->second->setTripID(tripID);
            createDayTrip(*(it->second));
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
    //LOG PENTRU ASTA

}

void TripRepository::update(const Trip& obj)
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

void TripRepository::remove(const Trip& obj)
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

std::vector<Trip*> TripRepository::getAll()
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

int TripRepository::getIdForLastInsertedTrip()
{
    std::string query = "SELECT TOP(1) TripID from Trips ORDER BY TripID DESC";
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru query last trip id");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare query last trip id");
    }
    SQLINTEGER ID;
    SQLBindCol(stmt, 1, SQL_C_LONG, &ID, 0, NULL);

    if (SQLFetch(stmt) == SQL_SUCCESS)
    {
        return ID;
    }
    else
    {
        throw std::runtime_error{ "Nu s a reusit executarea queryului pentru last id trip" };
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "queried last trip id");
}

void TripRepository::createDayTrip(const DayTrip& obj)
{
    std::string tripID, dayNumber, accID, attID, routeID;
    tripID = std::to_string(obj.getTripID());
    dayNumber = std::to_string(obj.getDayNumber());
    accID = std::to_string(obj.getAccommodation()->getID());
    attID = std::to_string(obj.getAttraction()->getId());
    routeID = std::to_string(obj.getRoute()->getId());
    std::string query = "EXEC AddDayTrip " + tripID + ", " + dayNumber +", " 
                        +accID + ", " + attID+ ", " + routeID+";";
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement exec AddDayTrip");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare insert daytrip");
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Inserted new daytrip");

}

std::vector<Trip*> TripRepository::getAllForUserID(int user_id)
{
    std::vector<Trip*> trips;
    std::string id = std::to_string(user_id);
    std::string query = "SELECT * FROM Trips WHERE UserID=" + id+ ";";
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement SELECT * FROM TRIPS");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare query all trips for user");
    }

    SQLINTEGER tripID, userID;
    SQLCHAR startDate[100], endDate[100];
    SQLINTEGER duration;
    SQLCHAR isConfirmed;
    SQLDOUBLE totalCost;

    SQLBindCol(stmt, 1, SQL_C_SLONG, &tripID, 0, NULL);    
    SQLBindCol(stmt, 2, SQL_C_SLONG, &userID, 0, NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, startDate, sizeof(startDate), NULL); 
    SQLBindCol(stmt, 4, SQL_C_CHAR, endDate, sizeof(endDate), NULL);  
    SQLBindCol(stmt, 5, SQL_C_LONG, &duration, 0, NULL);  
    SQLBindCol(stmt, 6, SQL_C_BIT, &isConfirmed, 0, NULL);   
    SQLBindCol(stmt, 7, SQL_C_DOUBLE, &totalCost, 0, NULL);  

    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        Trip* trip = new Trip;
        trip->setConfirmed(isConfirmed);
        trip->setDuration(duration);
        trip->setStartDate(std::string(reinterpret_cast<char*>(startDate)));
        trip->setEndDate(std::string(reinterpret_cast<char*>(endDate)));
        trip->setTotalCost(totalCost);
        trip->setUserID(userID);
        trip->setConfirmed(isConfirmed);
        trip->setID(tripID);
        trips.push_back(trip);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "queried all trips for a user");
    for (Trip* tr : trips)
    {
       std::vector<DayTrip *> dt= getDayTripsForTrip(tr->getID());
       for (DayTrip* d : dt)
       {
           tr->addDayTrip(d->getDayNumber() - 1, d);
       }

    }
    return trips;
}

std::vector<DayTrip*> TripRepository::getDayTripsForTrip(int trip_id)
{
    std::vector<DayTrip*> daytrips;
    std::string tripId = std::to_string(trip_id);
    std::string query = "SELECT * FROM TripsDays WHERE TripID =" +tripId + ";";

    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement select * from TripsDays");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare select daytrip");
    }
    SQLINTEGER id, tripID, accommodationID, attractionID, routeID;
    SQLDOUBLE dayNumber;

    SQLBindCol(stmt, 1, SQL_C_SLONG, &id, 0, NULL);          
    SQLBindCol(stmt, 2, SQL_C_SLONG, &tripID, 0, NULL);        
    SQLBindCol(stmt, 3, SQL_C_DOUBLE, &dayNumber, 0, NULL);     
    SQLBindCol(stmt, 4, SQL_C_SLONG, &accommodationID, 0, NULL); 
    SQLBindCol(stmt, 5, SQL_C_SLONG, &attractionID, 0, NULL);  
    SQLBindCol(stmt, 6, SQL_C_SLONG, &routeID, 0, NULL);     

    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        DayTrip* dt = new DayTrip{};
        iAccommodation* acc = FactoryAccommodations::makeApartament();
        iAttraction* att = FactoryAttraction::makeCulturalAttraction();
        TransportationRoute* route = new TransportationRoute();
        acc->setId(accommodationID);
        att->setId(attractionID);
        route->setId(routeID);
        dt->setAccommodation(acc);
        dt->setAttraction(att);
        dt->setRoute(route);
        dt->setDayNumber(dayNumber);
        dt->setTripID(trip_id);
        dt->setID(id);
        daytrips.push_back(dt);
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "queried daytrip");
    return daytrips;
}

void TripRepository::createGeneratedTrip(const Trip& obj)
{
    std::string id, duration, isConfirmed, totalCost;
    id = std::to_string(obj.getUserID());
    duration = std::to_string(obj.getDuration());
    isConfirmed = std::to_string(obj.isConfirmed());
    totalCost = std::to_string(obj.getTotalCost());

    std::string query = "EXEC CreateGeneratedTrip " + id + ", '" + obj.getStartingDate() + "','" + obj.getEndingDate() + "', " + duration + ", " + isConfirmed + ", " + totalCost + ";";
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement exec CreateGeneratedTrip");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare inserare GeneratedTrip");
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Inserted new generated trip");

    try
    {
        int tripID = getIdForLastInstertedGeneratedTrip();
        std::map<int, DayTrip*> organizare = obj.getDayTrips();
        for (auto it = organizare.begin(); it != organizare.end(); it++)
        {
            it->second->setTripID(tripID);
            createGeneratedDayTrip(*(it->second));
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}

void TripRepository::createGeneratedDayTrip(const DayTrip& obj)
{
    std::string tripID, dayNumber, accID, attID, routeID;
    tripID = std::to_string(obj.getTripID());
    dayNumber = std::to_string(obj.getDayNumber());
    accID = std::to_string(obj.getAccommodation()->getID());
    attID = std::to_string(obj.getAttraction()->getId());
    routeID = std::to_string(obj.getRoute()->getId());
    std::string query = "EXEC AddGeneratedDayTrip " + tripID + ", " + dayNumber + ", "
        + accID + ", " + attID + ", " + routeID + ";";
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement exec AddGeneratedDayTrip");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare insert generated daytrip");
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Inserted new generated daytrip");
}

int TripRepository::getIdForLastInstertedGeneratedTrip()
{
    std::string query = "SELECT TOP(1) TripID from GeneratedTrips ORDER BY TripID DESC";
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru query last generated trip id");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare query last generated trip id");
    }
    SQLINTEGER ID;
    SQLBindCol(stmt, 1, SQL_C_LONG, &ID, 0, NULL);

    if (SQLFetch(stmt) == SQL_SUCCESS)
    {
        return ID;
    }
    else
    {
        throw std::runtime_error{ "Nu s a reusit executarea queryului pentru last id generated trip" };
    }

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "queried last generated trip id");
}

std::vector<int> TripRepository::getMostRecentGeneratedTripsIDS(int n_recent)
{
    std::vector<int> tripIDs;
    try {
        std::string query =
            "SELECT TOP(" + std::to_string(n_recent) + ") "
            "    TripID "
            "FROM "
            "    GeneratedTrips "
            "ORDER BY "
            "    TripID DESC";

        SQLHSTMT stmt;
        SQLRETURN ret;

        ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
        if (!SQL_SUCCEEDED(ret)) {
            throw std::runtime_error("Eroare handler pentru statement getMostRecentGeneratedTripsIDS");
        }

        ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
        if (!SQL_SUCCEEDED(ret)) {
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            Logger::getInstance()->logDBActions(LogStatus::ERROR_, "Queried getMostRecentGeneratedTripsIDS");
            throw std::runtime_error("Eroare executare query getMostRecentGeneratedTripsIDS");
        }

        SQLINTEGER tripID;

        SQLBindCol(stmt, 1, SQL_C_LONG, &tripID, 0, NULL);

        while (SQLFetch(stmt) == SQL_SUCCESS)
        {
            tripIDs.insert(tripIDs.begin(), tripID);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Queried getMostRecentGeneratedTripsIDS");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "\n";
    }

    return tripIDs;
}

void TripRepository::confirmTrip(int trip_id)
{
    std::string id = std::to_string(trip_id);
    std::string query = "EXEC ConfirmTrip " + id+";";
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru query confirmare trip");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare confirmare trip");
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Confirmed a trip");
}

void TripRepository::moveGeneratedTripToPermanentTripHistory(int trip_id)
{
    std::string id = std::to_string(trip_id);
    std::string query = "EXEC MoveGeneratedTripDays " + id + ";";
    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru query mutare trip generat automat");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare mutare trip generat automat");
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Moved generated trip into permanent trips");
}
