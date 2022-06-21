#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include "sqlite3.h"
#include "Question.h"
#include "Game.h"

class IDatabase
{
public:
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string pword) = 0;
	virtual void addNewUser(std::string username, std::string pword, std::string email) = 0;

	virtual int getUserId(std::string username) = 0;

	virtual std::vector<Question> getQuestions(int numQuestions) = 0;
	virtual float getPlayerAverageAnswerTime(std::string username) = 0;
	virtual void updateStatistics(std::string username, GameData playerGameData) = 0;
	virtual int getNumOfCorrectAnswers(std::string username) = 0;
	virtual int getNumOfTotalAnswers(std::string username) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;
	virtual std::vector<std::pair<std::string, int>> getHighscores() = 0;
};

