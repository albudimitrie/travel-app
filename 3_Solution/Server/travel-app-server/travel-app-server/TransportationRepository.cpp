#include "TransportationRepository.h"
#include "iTransportation.h"

void TransportationRepository::create(const iTransportation& obj)
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

void TransportationRepository::update(const iTransportation& obj)
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

void TransportationRepository::remove(const iTransportation& obj)
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}

std::vector<iTransportation*> TransportationRepository::getAll()
{
    throw std::runtime_error{ "Aceasta functie nu a fost implementata\n" };
}


iTransportation* TransportationRepository::getTransportationWithID(int id)
{
	std::string  str_id = std::to_string(id);
	iTransportation* tr = nullptr;
	std::string query = "SELECT TransportationID , Type, "
						"Company, Description, "
						"PricePerKm, Capacity, ComfortLevel FROM Transportation "
						"WHERE TransportationID =" + str_id + " ;";


    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement getTransportationWithID");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        throw std::runtime_error("Eroare executare query transporturi");
    }
    SQLINTEGER TransportationID, Capacity;
    SQLCHAR Type[101], Company[51], Description[8000], ComfortLevel[1000];
    SQLDOUBLE PricePerKm;

    SQLBindCol(stmt, 1, SQL_C_LONG, &TransportationID, 0, NULL);
    SQLBindCol(stmt, 2, SQL_C_CHAR, Type, sizeof(Type), NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, Company, sizeof(Company), NULL);
    SQLBindCol(stmt, 4, SQL_C_CHAR, Description, sizeof(Description), NULL);
    SQLBindCol(stmt, 5, SQL_C_DOUBLE, &PricePerKm, 0, NULL);
    SQLBindCol(stmt, 6, SQL_C_LONG, &Capacity, 0, NULL);
    SQLBindCol(stmt, 7, SQL_C_CHAR, ComfortLevel, sizeof(ComfortLevel), NULL);


    if (SQLFetch(stmt) == SQL_SUCCESS)
    {
        if (std::string(reinterpret_cast<char*>(Type)) == "PLANE")
        {
            tr = FactoryTransportation::makePlaneTransport();

        }
        else if (std::string(reinterpret_cast<char*>(Type)) == "TRAIN")
        {
            tr = FactoryTransportation::makeTrainTransport();
        }
        else if (std::string(reinterpret_cast<char*>(Type)) == "BUS")
        {
            tr = FactoryTransportation::makeBusTransportation();

        }
        tr->setId(TransportationID);
        tr->setComfortLevel(reinterpret_cast<char*>(ComfortLevel));
        tr->setCompany(reinterpret_cast<char*>(Company));
        tr->setDescription(reinterpret_cast<char*>(Description));
        tr->setAveragePricePerTrip(PricePerKm);
        tr->setCapacity(Capacity);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Queried Transportation");
    return tr;
}

std::vector<TransportationRoute*> TransportationRepository::getAllRoutes()
{
    std::vector<TransportationRoute*> rute;
    std::vector<int> transportation_ids;
    std::string query = "SELECT RouteID, TransportationID, "
                        "CityDeparture, CityArrival, "
                        "Distance, Duration FROM RoutesTransportation";


    SQLHSTMT stmt;
    SQLRETURN ret;

    ret = SQLAllocHandle(SQL_HANDLE_STMT, _db->getDBC(), &stmt);
    if (!SQL_SUCCEEDED(ret)) {
        throw std::runtime_error("Eroare handler pentru statement getALLRoutes");
    }

    ret = SQLExecDirectA(stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        SQLFreeHandle(SQL_HANDLE_STMT, stmt);
        Logger::getInstance()->logDBActions(LogStatus::ERROR_, "Queried transportation");
        throw std::runtime_error("Eroare executare query routes");
    }
    SQLINTEGER RouteID, TransportationID, Distance, Duration;
    SQLCHAR CityDeparture[1000], CityArrival[1000];



    SQLBindCol(stmt, 1, SQL_C_LONG, &RouteID, 0, NULL);
    SQLBindCol(stmt, 2, SQL_C_LONG, &TransportationID, 0, NULL);
    SQLBindCol(stmt, 3, SQL_C_CHAR, CityDeparture, sizeof(CityDeparture), NULL);
    SQLBindCol(stmt, 4, SQL_C_CHAR, CityArrival, sizeof(CityArrival), NULL);
    SQLBindCol(stmt, 5, SQL_C_LONG, &Distance, 0, NULL);
    SQLBindCol(stmt, 6, SQL_C_LONG, &Duration, 0, NULL);

    while (SQLFetch(stmt) == SQL_SUCCESS)
    {
        TransportationRoute* tr = new TransportationRoute;
        tr->setId(RouteID);
        tr->setDistance(Distance);
        tr->setDuration(Duration);
        tr->setArrival(reinterpret_cast<char*>(CityArrival));
        tr->setDeparture(reinterpret_cast<char*>(CityDeparture));
        rute.push_back(tr);
        transportation_ids.push_back(TransportationID);
    }
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    for (int i=0; i<rute.size();i++)
    {
        int id = transportation_ids[i];
        rute[i]->setTransport(getTransportationWithID(id));
    }
    Logger::getInstance()->logDBActions(LogStatus::SUCCES, "Queried transportations");
    return rute;

}

std::string TransportationRepository::getPhotoWithID(int id)
{
    std::string str_id = std::to_string(id);
    std::string query = "Select Image From Transportation Where TransportationID = " + str_id + " ;";

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

TransportationRoute* TransportationRepository::getNullTransportation()
{
    throw std::runtime_error{ "Nu a fost implementata functia getNullTransportation" };
}
