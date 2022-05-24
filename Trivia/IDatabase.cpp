#include "IDatabase.h"

IDatabase::IDatabase() : db(nullptr)
{
	std::string dbFileName = "trivia.sqlite";
	int res = sqlite3_open(dbFileName.c_str(), &(this->db));
	if (res != SQLITE_OK) {
		this->db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return;
	}

}

IDatabase::~IDatabase()
{
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
