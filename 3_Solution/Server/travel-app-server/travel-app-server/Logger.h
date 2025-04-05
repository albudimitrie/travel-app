#pragma once
#include <string>
#include <fstream>

namespace LogStatus
{
	enum STATUS{ERROR_ ,SUCCES};
};


class Logger
{
	static Logger* _instance;
	std::string _path;
	std::ofstream _fout;

	Logger() = default;
	~Logger() = default;
	Logger(const Logger& obj) = delete;
	Logger(Logger&& obj) = delete;

	std::string threatStatus(LogStatus::STATUS stat);
	void writeToFile(const std::string& log);
public:
	static Logger* getInstance();
	static void destroyInstance();
	void setPath(const std::string& path);
	void logDBActions(LogStatus::STATUS status, const std::string& action);
	void logSockActions(LogStatus::STATUS status, const std::string& action);
	void logResponse(LogStatus::STATUS status, const std::string& action);
	void logAction(LogStatus::STATUS status, const std::string& action);

};

