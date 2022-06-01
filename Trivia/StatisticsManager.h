#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "SqliteDataBase.h"

class StatisticsManager
{
public:
	StatisticsManager(IDatabase* database) : m_database(database) {};

	std::vector<std::string> getHighScore();
	std::vector<std::string> getUserStatistics(std::string username);
private:
	IDatabase* m_database;
};
