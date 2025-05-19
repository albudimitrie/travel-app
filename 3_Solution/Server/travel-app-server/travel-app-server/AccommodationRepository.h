#pragma once
#include "iRepository.h"
class iAccommodation;
class AccommodationRepository : public ARepository<iAccommodation>
{
public:
	virtual void create(const iAccommodation& obj) override;
	virtual void update(const iAccommodation& obj) override;
	virtual void remove(const iAccommodation& obj) override;
	virtual std::vector<iAccommodation*> getAll() override;

	virtual ~AccommodationRepository() = default;
	int getNumberOfAccommodations();
	std::vector<int> getIDS();
	iAccommodation* getAccWithID(int id);
	std::string getPhotoPathOnID(int id);
	std::vector<iAccommodation*>getAccsWithFilters(std::string country, std::string climate, std::vector<std::string> type_options);
};

