#include "Logger.h"

Logger* Logger::_instance = nullptr;

Logger::Logger()
{
    
}
std::string Logger::threatStatus(LogStatus::STATUS stat)
{
    if (stat == 0)
    {
        return "[ERROR]";
    }
    else
    {
        return "[SUCCES]";
    }
}

void Logger::writeToFile(const std::string& log)
{
    _fout << log;
}

Logger* Logger::getInstance()
{
    if (!_instance)
    {
        _instance = new Logger();
    }
    return _instance;
}

void Logger::destroyInstance()
{

    if (_instance)
    {
        delete _instance;
        _instance = nullptr;
    }
}

void Logger::setPath(const std::string& path)
{
    this->_path = path;
    _fout.open(path.c_str(), std::ios::app);

}

void Logger::logDBActions(LogStatus::STATUS status, const std::string& action)
{
    DateTime _date;
    std::string date = _date.extractFormattedTime();
    std::string LOG = date + "[DB]" + threatStatus(status);
    LOG += "--" + action + "--\n";
    std::cout << LOG;
    writeToFile(LOG);
}

void Logger::logSockActions(LogStatus::STATUS status, const std::string& action)
{
    DateTime _date;
    std::string date = _date.extractFormattedTime();
    std::string LOG = date+ "[SOCKET]" + threatStatus(status);
    LOG += "--" + action + "--\n";
    std::cout << LOG;
    writeToFile(LOG);
}

void Logger::logResponse(LogStatus::STATUS status, const std::string& action)
{
    DateTime _date;
    std::string date = _date.extractFormattedTime();
    std::string LOG = date+"[RESPONSE]" + threatStatus(status);
    LOG += "--" + action + "--\n";
    std::cout << LOG;
    writeToFile(LOG);
}

void Logger::logAction(LogStatus::STATUS status, const std::string& action)
{
    DateTime _date;
    std::string date = _date.extractFormattedTime();
    std::string LOG = date +"[ACTION]" + threatStatus(status);
    LOG += "--" + action + "--\n";
    std::cout << LOG;
    writeToFile(LOG);
}
