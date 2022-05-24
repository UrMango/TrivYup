#include "IDatabase.h"

IDatabase::IDatabase() : db(nullptr)
{
	std::string dbFileName = "trivia.sqlite";
	int res = sqlite3_open(dbFileName.c_str(), &(this->db));
	if (res != SQLITE_OK) {
		this->db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		_exit(0);
	}

	res = sqlite3_exec(db, "CREATE TABLE USERS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, USERNAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);", nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
	}
}

IDatabase::~IDatabase()
{
	sqlite3_close(this->db);
	db = nullptr;

	delete this->errMessage;
}

bool IDatabase::doesUserExist(std::string username)
{
	return false;
}

bool IDatabase::doesPasswordMatch(std::string pword, std::string pword2)
{
	return false;
}

void IDatabase::addNewUser(std::string username, std::string pword, std::string email)
{
}
