#include "DateTime.h"
#include <string>

DateTime::DateTime()
{

	std::time_t time = std::time(nullptr);
	std::tm* now = std::localtime(&time);
	_year = now->tm_year + 1900;
	_month = now->tm_mon+1;
	_day = now->tm_mday;
	_hour = now->tm_hour;
	_minute = now->tm_min;
	_second = now->tm_sec;
}

std::string DateTime::extractFormattedTime()
{
	std::string f = "[";
	f += std::to_string(_year);
	f += "-";

	f += std::to_string(_month);
	f += "-";

	f += std::to_string(_day);
	f += "  ";

	f += std::to_string(_hour);
	f += ":";

	f += std::to_string(_minute);
	f += ":";

	f += std::to_string(_second);
	f += "]";
	return f;
}
