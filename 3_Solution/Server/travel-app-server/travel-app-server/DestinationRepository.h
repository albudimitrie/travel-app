#pragma once
#include "iRepository.h"
class Destination;
class DestinationRepository : public ARepository<Destination>
{
public:
	virtual void create(const Destination& obj) override;
	virtual void update(const Destination& obj) override;
	virtual void remove(const Destination& obj) override;
	virtual std::vector<Destination*> getAll() override;
	virtual std::vector<Destination*> getByFilters(std::vector<Filter*>) override;
	virtual ~DestinationRepository() = default;
};

