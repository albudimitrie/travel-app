#include "AttractionRepository.h"
#include "iAttraction.h"
#include "Destination.h"
#include "DestinationRepository.h"
#include <iostream>

void AttractionRepository::create(const iAttraction& obj)
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

void AttractionRepository::update(const iAttraction& obj)
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

void AttractionRepository::remove(const iAttraction& obj)
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

std::vector<iAttraction*> AttractionRepository::getAll()
{
    DestinationRepository repo;

    std::vector<Destination*>vectorDest = repo.getAll();
	std::vector<iAttraction*> atractii;
	std::string query = "SELECT AttractionID, DestinationID, Name, "
						"Description, Category, TicketPrice "
						"FROM Attractions";

	SQLHSTMT stmt;
	SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement getAllAttractions");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        Logger::getInstance()->logDBActions(LogStatus::ERROR_, "Queried attraction");
        throw std::runtime_error("Eroare executare query atractii");
    }
    SQLINTEGER attractionID, destinationID;
    SQLCHAR name[101], category[51], description[8000];
    SQLDOUBLE ticketPrice;

    SQLBindCol(stmt, 1, SQL_C_LONG, &attractionID, 0, NULL);
    SQLBindCol(stmt, 2, SQL_C_LONG, &destinationID, 0, NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, name, sizeof(name), NULL);
    SQLBindCol(stmt, 4, SQL_C_CHAR, description, sizeof(description), NULL);
    SQLBindCol(stmt, 5, SQL_C_CHAR, category, sizeof(category), NULL);
    SQLBindCol(stmt, 6, SQL_C_DOUBLE, &ticketPrice, 0, NULL);


    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        iAttraction* att = nullptr;
        if (std::string(reinterpret_cast<char *>(category)) == "CULTURAL")
        { 
            att = FactoryAttraction::makeCulturalAttraction();

        }
        else if (std::string(reinterpret_cast<char*>(category)) == "RELIGIOUS")
        {
            att = FactoryAttraction::makeReligiousAttraction();
        }
        else if (std::string(reinterpret_cast<char*>(category)) == "MUSICAL")
        {
            att = FactoryAttraction::makeMusicalAttraction();

        }

        att->setId(attractionID);
        att->setName(reinterpret_cast<char*>(name));
        att->setDescription(reinterpret_cast<char*>(description));
        att->setCategory(reinterpret_cast<char*>(category));
        att->setTicketPrice(ticketPrice);
        Destination* destinatie = nullptr;
        for (Destination* destination : vectorDest)
        {
            if (destination->getId() == destinationID)
            {
                destinatie = destination;
            }
        }
        att->setDestination(destinatie);
        atractii.push_back(att);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Queried attractions");
	return atractii;
}


std::vector<iAttraction*> AttractionRepository::getAttWithFilters(std::string country, std::string climate, std::vector<std::string> category_options)
{
    std::vector<iAttraction*> attractions;
    bool hasAnyCategory = false;
    for (const auto& category : category_options) {
        if (category == "Any" || category == "any") {
            hasAnyCategory = true;
            break;
        }
    }

    try {
        std::string query =
            "SELECT "
            "    A.AttractionID, "
            "    A.Name, "
            "    A.Description, "
            "    A.Category, "
            "    A.TicketPrice, "
            "    D.DestinationID, "
            "    D.Name AS DestinationName, "
            "    D.Country, "
            "    D.City, "
            "    D.Climate "
            "FROM "
            "    Attractions A "
            "INNER JOIN "
            "    Destinations D ON A.DestinationID = D.DestinationID "
            "WHERE "
            "    D.IsActive = 1";

        if (country != "any" || country != "Any") {
            query += " AND D.Country = '" + country + "'";
        }
        if (climate != "Any") {
            query += " AND D.Climate = '" + climate + "'";
        }

        if (!hasAnyCategory && !category_options.empty()) {
            query += " AND (";
            for (size_t i = 0; i < category_options.size(); ++i) {
                if (i > 0) {
                    query += " OR ";
                }
                query += "A.Category = '" + category_options[i] + "'";
            }
            query += ")";
        }
        SQLHSTMT stmt;
        SQLRETURN ret;

        ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
        if (!SQL_SUCCEEDED(ret)) {
            throw std::runtime_error("Eroare handler pentru statement getAttractionsWithFilter");
        }

        ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
        if (!SQL_SUCCEEDED(ret)) {
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            Logger::getInstance()->logDBActions(LogStatus::ERROR_, "Queried getAttractionsWithFilter");
            throw std::runtime_error("Eroare executare query getAttractionsWithFilter");
        }
        SQLINTEGER attractionID, destinationID;
        SQLCHAR name[256], description[4000], category[50], image[256];
        SQLCHAR destinationName[256], countryResult[50], city[50], climateResult[50];
        SQLDOUBLE ticketPrice;
        SQLLEN lenAttrID, lenName, lenDesc, lenCategory, lenTicket, lenImage, lenDestID, lenDestName, lenCountry, lenCity, lenClimate;

        SQLBindCol(stmt, 1, SQL_C_LONG, &attractionID, 0, &lenAttrID);
        SQLBindCol(stmt, 2, SQL_C_CHAR, name, sizeof(name), &lenName);
        SQLBindCol(stmt, 3, SQL_C_CHAR, description, sizeof(description), &lenDesc);
        SQLBindCol(stmt, 4, SQL_C_CHAR, category, sizeof(category), &lenCategory);
        SQLBindCol(stmt, 5, SQL_C_DOUBLE, &ticketPrice, 0, &lenTicket);
        SQLBindCol(stmt, 6, SQL_C_LONG, &destinationID, 0, &lenDestID);
        SQLBindCol(stmt, 7, SQL_C_CHAR, destinationName, sizeof(destinationName), &lenDestName);
        SQLBindCol(stmt, 8, SQL_C_CHAR, countryResult, sizeof(countryResult), &lenCountry);
        SQLBindCol(stmt, 9, SQL_C_CHAR, city, sizeof(city), &lenCity);
        SQLBindCol(stmt, 10, SQL_C_CHAR, climateResult, sizeof(climateResult), &lenClimate);

        while (SQLFetch(stmt) == SQL_SUCCESS)
        {
            iAttraction* att = nullptr;
            std::string cat = reinterpret_cast<char*>(category);
            if (cat == "RELIGIOUS")
            {
                att = FactoryAttraction::makeReligiousAttraction();
            }
            if (cat == "CULTURAL")
            {
                att = FactoryAttraction::makeCulturalAttraction();
            }
            if (cat == "MUSICAL")
            {
                att = FactoryAttraction::makeMusicalAttraction();
            }
            att->setId(attractionID);
            att->setName(reinterpret_cast<char*>(name));
            att->setDescription(reinterpret_cast<char*>(description));
            att->setCategory(reinterpret_cast<char*>(category));
            att->setTicketPrice(ticketPrice);

            Destination* destinatie = new Destination();
            destinatie->setId(destinationID);
            destinatie->setName(reinterpret_cast<char*>(destinationName));
            destinatie->setCountry(reinterpret_cast<char*>(countryResult));
            destinatie->setCity(reinterpret_cast<char*>(city));
            destinatie->setClimate(reinterpret_cast<char*>(climateResult));

            att->setDestination(destinatie);
            attractions.push_back(att);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Queried getAttractionsWithFilter");

    }
    catch (const std::exception& e) 
    {
        std::cout << e.what() << "\n";
    }

    return attractions;
}

std::string AttractionRepository::getPhotoWithID(int id)
{
    std::string str_id = std::to_string(id);
    std::string query = "Select Image From Attractions Where AttractionID = " + str_id + " ;";

    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement getPhotowithId");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare query PhotoWithID");
    }
    SQLCHAR path[256];
    SQLBindCol(stmt, 1, SQL_C_CHAR, path, sizeof(path), NULL);
    if (SQLFetch(stmt) == SQL_SUCCESS)
    {
        return reinterpret_cast<char*>(path);
    }
    return std::string();

}
