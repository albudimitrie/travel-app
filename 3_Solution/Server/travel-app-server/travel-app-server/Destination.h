#pragma once
#include <string>
class Destination
{
	int _id;
	std::string _name,
				_country,
				_city,
				_description,
				_climate;
	bool _isActive;
public:
    void setId(int id);
    void setName(const std::string& name);
    void setCountry(const std::string& country);
    void setCity(const std::string& city);
    void setDescription(const std::string& description);
    void setClimate(const std::string& climate);
    void setIsActive(bool isActive);

    int getId() const;
    std::string getName() const;
    std::string getCountry() const;
    std::string getCity() const;
    std::string getDescription() const;
    std::string getClimate() const;
    bool isActive() const;
};

