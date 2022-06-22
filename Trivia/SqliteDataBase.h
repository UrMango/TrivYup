#pragma once
#include "IDatabase.h"
#include <exception>

class SqliteDataBase : public IDatabase
{
public:
	SqliteDataBase();
	~SqliteDataBase();

	/* V1*/
	bool doesUserExist(std::string username) override;
	bool doesPasswordMatch(std::string username, std::string pword) override;
	void addNewUser(std::string username, std::string pword, std::string email) override;

	/* V2*/
	//Question getQuestion(int id) override;
	std::vector<Question> getQuestions(int numQuestions) override;
	void updateStatistics(std::string username, GameData playerGameData) override;

	//getters
	float getPlayerAverageAnswerTime(std::string username) override;
	int getNumOfCorrectAnswers(std::string username) override;
	int getNumOfTotalAnswers(std::string username) override;
	int getNumOfPlayerGames(std::string username) override;
	std::vector<std::pair<std::string, int>> getHighscores() override;
	int getUserId(std::string username) override;

private:
	sqlite3* db;
	char* errMessage;
	Question question;
	int numReturn;
	float floatReturn;
	std::mutex _dataBasetx;

};
