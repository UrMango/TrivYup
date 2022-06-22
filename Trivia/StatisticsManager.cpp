#include "StatisticsManager.h"

std::vector<std::string> StatisticsManager::getHighScore()
{
    const int LENGTH_TO_RET = 3;

    std::vector<std::pair<std::string, int>> highscoresList = this->m_database->getHighscores();
    std::vector<std::string> highscores;

    for (int i = 0; i < LENGTH_TO_RET; i++)
    {
        if(highscoresList.size() > i)
            highscores.push_back(highscoresList[i].first);
    }    

    return highscores;
}

std::vector<std::string> StatisticsManager::getUserStatistics(std::string username)
{
    std::vector<std::string> userStats;

    userStats.push_back(std::to_string(this->m_database->getPlayerAverageAnswerTime(username)));
    userStats.push_back(std::to_string(this->m_database->getNumOfCorrectAnswers(username)));
    userStats.push_back(std::to_string(this->m_database->getNumOfTotalAnswers(username)));
    userStats.push_back(std::to_string(this->m_database->getNumOfPlayerGames(username)));

    return userStats;
}
