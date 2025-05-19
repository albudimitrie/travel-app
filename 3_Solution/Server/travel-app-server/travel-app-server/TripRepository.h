#pragma once
#include "iRepository.h"
#include "Trip.h"

class DayTrip;
class TripRepository :
    public ARepository<Trip>
{
public:
	virtual void create(const Trip& obj) override;
	virtual void update(const Trip& obj) override;
	virtual void remove(const Trip& obj)override;
	virtual std::vector<Trip*> getAll() override;
	int getIdForLastInsertedTrip();
	void createDayTrip(const DayTrip& obj);
	std::vector<Trip*>getAllForUserID(int user_id);
	std::vector<DayTrip*>getDayTripsForTrip(int trip_id);
	void createGeneratedTrip(const Trip& obj);
	void createGeneratedDayTrip(const DayTrip& obj);
	int getIdForLastInstertedGeneratedTrip();
	std::vector<int> getMostRecentGeneratedTripsIDS(int n_recent);
	void confirmTrip(int trip_id);
	void moveGeneratedTripToPermanentTripHistory(int trip_id);
};

