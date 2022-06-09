#pragma once
#include "SqliteDataBase.h"


class StatisticsManager
{
public:
	StatisticsManager(IDatabase* database) : m_database(database) {};
	~StatisticsManager() = default;

	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string userName);

private:
	IDatabase* m_database;
};
