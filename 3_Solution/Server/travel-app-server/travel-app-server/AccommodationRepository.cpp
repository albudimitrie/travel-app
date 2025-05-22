#include "AccommodationRepository.h"
#include "iAccommodation.h"
#include "DestinationRepository.h"
#include "Destination.h"
#include <iostream>

void AccommodationRepository::create(const iAccommodation& obj)
{
}

void AccommodationRepository::update(const iAccommodation& obj)
{
}

void AccommodationRepository::remove(const iAccommodation& obj)
{
}

std::vector<iAccommodation*> AccommodationRepository::getAll()
{
    std::vector<iAccommodation*> accommodations;

    std::string query = "SELECT AccommodationID, DestinationID, Name, Type, "
        "Address, Description, PricePerNight, Facilities "
        "FROM Accommodations "
        "ORDER BY AccommodationID DESC";

    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement getAllAccommodations");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare query destinatii");
    }
    SQLINTEGER accommodationID, destinationID;
    SQLCHAR name[101], type[51], address[256], description[8000], facilities[8000];
    SQLDOUBLE pricePerNight;

    SQLBindCol(stmt, 1, SQL_C_LONG, &accommodationID, 0, NULL);
    SQLBindCol(stmt, 2, SQL_C_LONG, &destinationID, 0, NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, name, sizeof(name), NULL);
    SQLBindCol(stmt, 4, SQL_C_CHAR, type, sizeof(type), NULL);
    SQLBindCol(stmt, 5, SQL_C_CHAR, address, sizeof(address), NULL);
    SQLBindCol(stmt, 6, SQL_C_CHAR, description, sizeof(description), NULL);
    SQLBindCol(stmt, 7, SQL_C_DOUBLE, &pricePerNight, 0, NULL);
    SQLBindCol(stmt, 8, SQL_C_CHAR, facilities, sizeof(facilities), NULL);

    while (SQLFetch(stmt) == SQL_SUCCESS) {
        iAccommodation* accommodation = nullptr;
        if (std::string(reinterpret_cast<char *>(type)) == "HOTEL")
        {
            accommodation = FactoryAccommodations::makeHotel();
        }
        else if (std::string(reinterpret_cast<char*>(type)) == "APARTAMENT")
        {
            accommodation = FactoryAccommodations::makeApartament();
        }
        else if (std::string(reinterpret_cast<char*>(type)) == "PENSIUNE")
        {
            accommodation = FactoryAccommodations::makePensiune();
        }
        if (!accommodation)
        {
            throw std::runtime_error{ "Nu exista acest tip de cazare\n" };
        }

        try
        {
            DestinationRepository _repo_dests;
            Destination* dest = _repo_dests.getDestinationWithID(destinationID);
            accommodation->setDestination(dest);
        }
        catch (std::exception& e)
        {
            std::cout << e.what();
        }
        accommodation->setId(accommodationID);
        accommodation->setName(reinterpret_cast<char*>(name));
        accommodation->setAddress(reinterpret_cast<char*>(address));
        accommodation->setDescription(reinterpret_cast<char*>(description));
        accommodation->setPricePerNight(pricePerNight);
        accommodation->setFacilities(reinterpret_cast<char*>(facilities));
        accommodations.push_back(accommodation);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Queried all accommodations");

    return accommodations;
}


int AccommodationRepository::getNumberOfAccommodations()
{
    std::string query = "SELECT COUNT(*) FROM Accommodations";

    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement GetNumberOfAccommodations");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare query numar destinatii");
    }
    SQLINTEGER number;
    SQLBindCol(stmt, 1, SQL_C_LONG, &number, 0, NULL);

    if (SQLFetch(stmt) == SQL_SUCCESS)
    {
        return number;
    }

    return 0;
}

std::vector<int> AccommodationRepository::getIDS()
{
    std::vector<int> ids;
    std::string query = "SELECT AccommodationID FROM Accommodations";

    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement getAllAccommodationsID");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare query accommodationsIDs");
    }

    SQLINTEGER id;
    SQLBindCol(stmt, 1, SQL_C_LONG, &id, 0, NULL);

    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        ids.push_back(id);
    }

    return ids;
}

iAccommodation* AccommodationRepository::getAccWithID(int id)
{
    std::string str_id = std::to_string(id);
    iAccommodation* accommodation = nullptr;

    std::string query = "SELECT AccommodationID, DestinationID, Name, Type, "
        "Address, Description, PricePerNight, Facilities "
        "FROM Accommodations "
        "WHERE AccommodationID = " + str_id + " "
        "ORDER BY AccommodationID DESC";

    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement getAccWithID");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare query AccommodationWithID");
    }
    SQLINTEGER accommodationID, destinationID;
    SQLCHAR name[101], type[51], address[256], description[8000], facilities[8000];
    SQLDOUBLE pricePerNight;

    SQLBindCol(stmt, 1, SQL_C_LONG, &accommodationID, 0, NULL);
    SQLBindCol(stmt, 2, SQL_C_LONG, &destinationID, 0, NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, name, sizeof(name), NULL);
    SQLBindCol(stmt, 4, SQL_C_CHAR, type, sizeof(type), NULL);
    SQLBindCol(stmt, 5, SQL_C_CHAR, address, sizeof(address), NULL);
    SQLBindCol(stmt, 6, SQL_C_CHAR, description, sizeof(description), NULL);
    SQLBindCol(stmt, 7, SQL_C_DOUBLE, &pricePerNight, 0, NULL);
    SQLBindCol(stmt, 8, SQL_C_CHAR, facilities, sizeof(facilities), NULL);

    if (SQLFetch(stmt) == SQL_SUCCESS) {
        if (std::string(reinterpret_cast<char*>(type)) == "HOTEL")
        {
            accommodation = FactoryAccommodations::makeHotel();
        }
        else if (std::string(reinterpret_cast<char*>(type)) == "APARTAMENT")
        {
            accommodation = FactoryAccommodations::makeApartament();
        }
        else if (std::string(reinterpret_cast<char*>(type)) == "PENSIUNE")
        {
            accommodation = FactoryAccommodations::makePensiune();
        }
        if (!accommodation)
        {
            throw std::runtime_error{ "Nu exista acest tip de cazare\n" };
        }

        try
        {
            DestinationRepository _repo_dests;
            Destination* dest = _repo_dests.getDestinationWithID(destinationID);
            accommodation->setDestination(dest);
        }
        catch (std::exception& e)
        {
            std::cout << e.what();
        }
        accommodation->setId(accommodationID);
        accommodation->setName(reinterpret_cast<char*>(name));
        accommodation->setAddress(reinterpret_cast<char*>(address));
        accommodation->setDescription(reinterpret_cast<char*>(description));
        accommodation->setPricePerNight(pricePerNight);
        accommodation->setFacilities(reinterpret_cast<char*>(facilities));
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Queried accommodation with id " + std::to_string(accommodationID));

    return accommodation;
}

std::string AccommodationRepository::getPhotoPathOnID(int id)
{
    std::string str_id = std::to_string(id);
    std::string query = "Select Image From Accommodations Where AccommodationID = " + str_id + " ;";

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

std::vector<iAccommodation*> AccommodationRepository::getAccsWithFilters(std::string country, std::string climate, std::vector<std::string> type_options)
{
    std::vector<iAccommodation*> accommodations;
    bool hasAnyType = false;
    for (const auto& type : type_options) {
        if (type == "Any" || type == "any") {
            hasAnyType = true;
            break;
        }
    }

    try {
        std::string query =
            "SELECT "
            "    A.AccommodationID, "
            "    A.Name, "
            "    A.Type, "
            "    A.Address, "
            "    A.Description, "
            "    A.PricePerNight, "
            "    A.Facilities, "
            "    D.DestinationID, "
            "    D.Name AS DestinationName, "
            "    D.Country, "
            "    D.City, "
            "    D.Climate "
            "FROM "
            "    Accommodations A "
            "INNER JOIN "
            "    Destinations D ON A.DestinationID = D.DestinationID "
            "WHERE "
            "    D.IsActive = 1";

        if (country != "any" && country != "Any") {
            query += " AND D.Country = '" + country + "'";
        }
        if (climate != "Any") {
            query += " AND D.Climate = '" + climate + "'";
        }

        if (!hasAnyType && !type_options.empty()) {
            query += " AND (";
            for (int i = 0; i < type_options.size(); ++i) {
                if (i > 0) {
                    query += " OR ";
                }
                query += "A.Type = '" + type_options[i] + "'";
            }
            query += ")";
        }

        SQLHSTMT stmt;
        SQLRETURN ret;

        ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
        if (!SQL_SUCCEEDED(ret)) {
            throw std::runtime_error("Eroare handler pentru statement getAccommodationsWithFilter");
        }

        ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
        if (!SQL_SUCCEEDED(ret)) {
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            Logger::getInstance()->logDBActions(LogStatus::ERROR_, "Queried getAccommodationsWithFilter");
            throw std::runtime_error("Eroare executare query getAccommodationsWithFilter");
        }

        SQLINTEGER accommodationID, destinationID;
        SQLCHAR name[256], type[50], address[256], description[4000], facilities[1000];
        SQLCHAR destinationName[256], countryResult[50], city[50], climateResult[50];
        SQLDOUBLE pricePerNight;
        SQLLEN lenAccID, lenName, lenType, lenAddress, lenDesc, lenPrice, lenFacilities;
        SQLLEN lenDestID, lenDestName, lenCountry, lenCity, lenClimate;

        SQLBindCol(stmt, 1, SQL_C_LONG, &accommodationID, 0, &lenAccID);
        SQLBindCol(stmt, 2, SQL_C_CHAR, name, sizeof(name), &lenName);
        SQLBindCol(stmt, 3, SQL_C_CHAR, type, sizeof(type), &lenType);
        SQLBindCol(stmt, 4, SQL_C_CHAR, address, sizeof(address), &lenAddress);
        SQLBindCol(stmt, 5, SQL_C_CHAR, description, sizeof(description), &lenDesc);
        SQLBindCol(stmt, 6, SQL_C_DOUBLE, &pricePerNight, 0, &lenPrice);
        SQLBindCol(stmt, 7, SQL_C_CHAR, facilities, sizeof(facilities), &lenFacilities);
        SQLBindCol(stmt, 8, SQL_C_LONG, &destinationID, 0, &lenDestID);
        SQLBindCol(stmt, 9, SQL_C_CHAR, destinationName, sizeof(destinationName), &lenDestName);
        SQLBindCol(stmt, 10, SQL_C_CHAR, countryResult, sizeof(countryResult), &lenCountry);
        SQLBindCol(stmt, 11, SQL_C_CHAR, city, sizeof(city), &lenCity);
        SQLBindCol(stmt, 12, SQL_C_CHAR, climateResult, sizeof(climateResult), &lenClimate);

        while (SQLFetch(stmt) == SQL_SUCCESS)
        {
            iAccommodation* acc = nullptr;
            std::string accType = reinterpret_cast<char*>(type);
            if (accType == "HOTEL")
            {
                acc = FactoryAccommodations::makeHotel();
            }
            if (accType == "PENSIUNE")
            {
                acc = FactoryAccommodations::makePensiune();
            }
            if (accType == "APARTAMENT")
            {
                acc = FactoryAccommodations::makeApartament();
            }

            acc->setId(accommodationID);
            acc->setName(reinterpret_cast<char*>(name));
            acc->setAddress(reinterpret_cast<char*>(address));
            acc->setDescription(reinterpret_cast<char*>(description));
            acc->setPricePerNight(pricePerNight);
            acc->setFacilities(reinterpret_cast<char*>(facilities));

            Destination* destinatie = new Destination;
            destinatie->setId(destinationID);
            destinatie->setName(reinterpret_cast<char*>(destinationName));
            destinatie->setCountry(reinterpret_cast<char*>(countryResult));
            destinatie->setCity(reinterpret_cast<char*>(city));
            destinatie->setClimate(reinterpret_cast<char*>(climateResult));

            acc->setDestination(destinatie);
            accommodations.push_back(acc);
        }

        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Queried getAccommodationsWithFilter");
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "\n";
    }

    return accommodations;
}
