#pragma once

#include <vector>
#include "DataBaseCon.h"


class Filter;

//REPO PATTERN FOR DATA LAYER COMMUNICATION, CRUD OPERATIONS + FILTERING ON SQL SERVER DATABASE
template <typename T>
class iRepository
{
public:

	virtual void create(const T& obj) = 0;
	virtual void update(const T& obj) = 0;
	virtual void remove(const T& obj) = 0;
	virtual std::vector<T*> getAll() = 0;
	virtual std::vector<T*> getByFilters(std::vector<Filter *>) = 0;
	virtual ~iRepository() = default;

};





//------------------------------------------------------------------------------------------------------------





template<typename T>
class ARepository : public iRepository<T>
{
protected:
	DataBaseCon* _db;
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
	_db = nullptr;
}