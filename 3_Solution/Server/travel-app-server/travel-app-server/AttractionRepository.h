#pragma once
#include "iRepository.h"


class iAttraction;
class AttractionRepository :public ARepository<iAttraction>
{
public:
	virtual void create(const iAttraction& obj) override;
	virtual void update(const iAttraction& obj) override;
	virtual void remove(const iAttraction& obj) override;
	virtual std::vector<iAttraction*> getAll() override;
	virtual ~AttractionRepository() = default;
	std::vector<iAttraction*>getAttWithFilters(std::string country, std::string climate, std::vector<std::string> category_options);
	std::string getPhotoWithID(int id);
};

