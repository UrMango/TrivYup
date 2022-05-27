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
	void addNewUser(std::string username, std::string pword, std::string email) override;
private:
	sqlite3* db;
	char* errMessage;
};

