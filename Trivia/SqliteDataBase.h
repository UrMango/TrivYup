#pragma once
#include "IDatabase.h"
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
	std::list<Question> getQuestions() override;
	float getPlayerAverageAnswerTime(std::string username) override;
	int getNumOfCorrectAnswers(std::string username) override;
	int getNumOfTotalAnswers(std::string username) override;
	int getNumOfPlayerGames(std::string username) override;
private:
	sqlite3* db;
	char* errMessage;

	std::list<Question> questionList;
	int numReturn;
	float floatReturn;
};
