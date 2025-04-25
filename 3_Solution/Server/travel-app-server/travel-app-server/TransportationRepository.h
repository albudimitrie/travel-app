#pragma once
#include "iRepository.h"


class iTransportation;
class TransportationRepository : public ARepository<iTransportation>
{
public:
	virtual void create(const iTransportation& obj) override;
	virtual void update(const iTransportation& obj) override;
	virtual void remove(const iTransportation& obj) override;
	virtual std::vector<iTransportation*> getAll() override;
	virtual std::vector<iTransportation*> getByFilters(std::vector<Filter*>) override;
	virtual ~TransportationRepository() = default;
};

