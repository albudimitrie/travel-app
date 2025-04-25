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
	virtual std::vector<iAccommodation*> getByFilters(std::vector<Filter*>) override;
	virtual ~AccommodationRepository() = default;
};

