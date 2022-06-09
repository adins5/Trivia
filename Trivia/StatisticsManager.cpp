#include "StatisticsManager.h"


std::vector<std::string> StatisticsManager::getHighScore()
{
	return this->m_database->getHighScores();
}


std::vector<std::string> StatisticsManager::getUserStatistics(std::string userName)
{
	std::vector<std::string> statistics;
	statistics.push_back(std::to_string(this->m_database->getNumOfCorrectAnswer(userName)));
	statistics.push_back(std::to_string(this->m_database->getNumOfPlayerGames(userName)));
	statistics.push_back(std::to_string(this->m_database->getPlayerAverageAnswerTime(userName)));
	statistics.push_back(std::to_string(this->m_database->getNumOfTotalAnswers(userName)));
	statistics.push_back(std::to_string(this->m_database->getPlayerScore(userName)));

	return statistics;
}