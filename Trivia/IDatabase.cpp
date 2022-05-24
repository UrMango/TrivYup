#include "IDatabase.h"


#define BOOL_CB_NORES 0
#define BOOL_CB_FALSE 1
#define BOOL_CB_TRUE 2

/* 0 - noRes, 1 - false, 2 - true*/
int boolCallbackRes;

// Callbacks
int countSelectCallback(void* data, int argc, char** argv, char** azColName)
{
	if (argc > 0) 
		boolCallbackRes = BOOL_CB_TRUE;
	else 
		boolCallbackRes = BOOL_CB_FALSE;
	return SQLITE_OK;
}

IDatabase::IDatabase() : db(nullptr), errMessage(nullptr)
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
	int res;

	std::string query = "SELECT * FROM USERS WHERE USERNAME = '" + username + "';";
	res = sqlite3_exec(db, query.c_str(), countSelectCallback, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return true;
	}
	else
	{
		bool res = boolCallbackRes == BOOL_CB_TRUE;
		boolCallbackRes = BOOL_CB_NORES;

		return res;
	}
}

bool IDatabase::doesPasswordMatch(std::string username, std::string pword)
{
	return false;
}

void IDatabase::addNewUser(std::string username, std::string pword, std::string email)
{
}
