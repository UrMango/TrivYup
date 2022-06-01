#pragma once

#include <iostream>
#include <list>
#include "sqlite3.h"
#include "Question.h"

class IDatabase
{
public:
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string pword) = 0;
	virtual void addNewUser(std::string username, std::string pword, std::string email) = 0;

	virtual std::list<Question> getQuestions() = 0;
	virtual float getPlayerAverageAnswerTime(std::string username) = 0;
	virtual int getNumOfCorrectAnswers(std::string username) = 0;
	virtual int getNumOfTotalAnswers(std::string username) = 0;
	virtual int getNumOfPlayerGames(std::string username) = 0;
};

