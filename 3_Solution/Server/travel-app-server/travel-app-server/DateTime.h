#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <iomanip>
class DateTime
{
	int _year, _month, _day, _minute, _second, _hour;
public:
	DateTime();
	std::string extractFormattedTime();
};

