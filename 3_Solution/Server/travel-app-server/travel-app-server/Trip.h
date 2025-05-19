#pragma once
#include <string>
#include <map>

class DayTrip;

class Trip
{
	int _ID,
		_userID;
	std::string _startDate,
				_endDate;
	bool _isConfirmed;
	float _totalCost;
	float _duration;
	std::map<int, DayTrip*> _organizareZile;;

public:
	//-----------------------------------------------SETTERS--------------------------------------------------------------
	Trip();
	void setID(int id);
	void setUserID(int id);
	void setDuration(float duration);
	void setStartDate(std::string startDate);
	void setEndDate(std::string endDate);
	void setConfirmed(bool confirmed);
	void setTotalCost(float cost);
	float calculateTotalCost();
	//------------------------------------------------GETTERS-----------------------------------------------------------
	int getID()const ;
	int getUserID()const;
	float getDuration()const;
	std::string getStartingDate()const;
	std::string getEndingDate()const;
	bool isConfirmed()const;
	float getTotalCost()const;
	std::map<int, DayTrip*> getDayTrips()const;

	void addDayTrip(int dayNumber, DayTrip* dt);
	~Trip();

	//TODO get/set organizareZILE

};

