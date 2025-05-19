#pragma once
#include "iRepository.h"
#include "TransportationRoute.h"

class iTransportation;
class TransportationRepository : public ARepository<iTransportation>
{
public:
	virtual void create(const iTransportation& obj) override;
	virtual void update(const iTransportation& obj) override;
	virtual void remove(const iTransportation& obj) override;
	virtual std::vector<iTransportation*> getAll() override;
	virtual ~TransportationRepository() = default;
	iTransportation * getTransportationWithID(int id);
	std::vector<TransportationRoute*> getAllRoutes();
	std::string getPhotoWithID(int id);
	TransportationRoute* getNullTransportation();
	
};

