#pragma once

#include <string>
namespace utils {
	inline bool hasIllegalLoginChars(const std::string& username)
	{
		std::string ilegale = "-;!/\\";
		if (username.find_first_of(ilegale) != std::string::npos)
		{
			return true;
		}
		return false;
	}
}
