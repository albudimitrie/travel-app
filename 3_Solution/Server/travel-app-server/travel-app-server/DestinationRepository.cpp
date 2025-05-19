#include "DestinationRepository.h"
#include "Destination.h"
#include <iostream>

void DestinationRepository::create(const Destination& obj)
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

void DestinationRepository::update(const Destination& obj)
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

void DestinationRepository::remove(const Destination& obj)
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

std::vector<Destination*> DestinationRepository::getAll()
{
        std::vector<Destination*> destinations;

        std::string query = "SELECT DestinationID, Name, Country, City, "
            "Description, Climate , IsActive "
            "FROM Destinations "
            "WHERE IsActive = 1 "
            "ORDER BY DestinationID DESC";

        SQLHSTMT stmt;
        SQLRETURN ret;

        ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
        if (!SQL_SUCCEEDED(ret)) {
            throw std::runtime_error("Eroare handler pentru statement getAllDestinations");
        }

        ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
        if (!SQL_SUCCEEDED(ret)) {
            SQLFreeHandle(SQL_HANDLE_STMT, stmt);
            throw std::runtime_error("Eroare executare query destinatii");
        }

        SQLINTEGER destinationID;
        SQLCHAR name[256], city[256], country[256], description[256], climate[256];
        SQLLEN isActive;

        SQLBindCol(stmt, 1, SQL_C_LONG, &destinationID, 0, NULL);
        SQLBindCol(stmt, 2, SQL_C_CHAR, name, sizeof(name), NULL);
        SQLBindCol(stmt, 3, SQL_C_CHAR, country, sizeof(city), NULL);
        SQLBindCol(stmt, 4, SQL_C_CHAR, city, sizeof(country), NULL);
        SQLBindCol(stmt, 5, SQL_C_CHAR, description, sizeof(description), NULL);
        SQLBindCol(stmt, 6, SQL_C_CHAR, climate, sizeof(climate), NULL);
        SQLBindCol(stmt, 7, SQL_C_BIT, &isActive, 0, NULL);

        while (SQLFetch(stmt) == SQL_SUCCESS) {
            Destination * destination = new Destination;

            destination->setId(destinationID);
            destination->setName(reinterpret_cast<char*>(name));
            destination->setCity(reinterpret_cast<char *>(city));
            destination->setCountry(reinterpret_cast<char*>(country));
            destination->setClimate(reinterpret_cast<char*>(climate));
            destination->setDescription(reinterpret_cast<char*>(description));
            destination->setIsActive(isActive);
            destinations.push_back(destination);
        }
        Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Queried Destinations");

        SQLFreeHandle(SQL_HANDLE_STMT, stmt);

        return destinations;
}


Destination* DestinationRepository::getDestinationWithID(int id)
{
    Destination* destination = new Destination;
    std::string str_id = std::to_string(id);

    std::string query = "SELECT DestinationID, Name, Country, City, "
        "Description, Climate , IsActive "
        "FROM Destinations "
        "WHERE DestinationID = " + str_id + " "
        "ORDER BY DestinationID DESC";

    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        delete destination;
        throw std::runtime_error("Eroare handler pentru statement getAllDestinations");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLCHAR sqlState[6];
        SQLCHAR message[1000];
        SQLGetDiagRecA(SQL_HANDLE_STMT, stmt, 1, sqlState, NULL, message, sizeof(message), NULL);
        std::cout << "SQL Error: " << sqlState << " - " << message << std::endl;
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        delete destination;
        throw std::runtime_error("Eroare executare query destinatii");
    }

    SQLINTEGER destinationID;
    SQLCHAR name[256], city[256], country[256], description[256], climate[256];
    SQLLEN isActive;

    SQLBindCol(stmt, 1, SQL_C_LONG, &destinationID, 0, NULL);
    SQLBindCol(stmt, 2, SQL_C_CHAR, name, sizeof(name), NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, country, sizeof(country), NULL);
    SQLBindCol(stmt, 4, SQL_C_CHAR, city, sizeof(city), NULL);
    SQLBindCol(stmt, 5, SQL_C_CHAR, description, sizeof(description), NULL);
    SQLBindCol(stmt, 6, SQL_C_CHAR, climate, sizeof(climate), NULL);
    SQLBindCol(stmt, 7, SQL_C_BIT, &isActive, 0, NULL);

    if (SQLFetch(stmt) == SQL_SUCCESS) {

        destination->setId(destinationID);
        destination->setName(reinterpret_cast<char*>(name));
        destination->setCity(reinterpret_cast<char*>(city));
        destination->setCountry(reinterpret_cast<char*>(country));
        destination->setClimate(reinterpret_cast<char*>(climate));
        destination->setDescription(reinterpret_cast<char*>(description));
        destination->setIsActive(isActive);
    }
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "QUERIED DESTINATION WITH ID=" + str_id);

    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    return destination;
}
