#pragma once

#include <vector>
#include "DataBaseCon.h"
#include "Logger.h"


//REPO PATTERN FOR DATABASE LAYER COMMUNICATION, CRUD OPERATIONS(MOSTLY OF THEM CLASSES WILL DO THESE OPS)
template <typename T>
class iRepository
{
public:

	virtual void create(const T& obj) = 0;
	virtual void update(const T& obj) = 0;
	virtual void remove(const T& obj) = 0;
	virtual std::vector<T*> getAll() = 0;
	virtual ~iRepository() = default;

};
//------------------------------------------------------------------------------------------------------------

template<typename T>
class ARepository : public iRepository<T>
{
protected:
	DataBaseCon* _db;	//database connection needed for QUERYING
public:
	ARepository();
	virtual ~ARepository();
};

template <typename T>
inline ARepository<T>::ARepository()
{
	_db = DataBaseCon::getInstance();
}



template <typename T>
inline ARepository<T>::~ARepository()
{
	//not responsible for creating, also not responsible for destroying
	_db = nullptr;
}