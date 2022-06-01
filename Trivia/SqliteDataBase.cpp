#include "SqliteDataBase.h"

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

int getQuestionCallback(void* data, int argc, char** argv, char** azColName)
{
	std::list<Question> questionList = *((std::list<Question>*)data);

	int id;
	std::string question;
	std::string ans;
	std::string wrongAns;
	std::string wrongAns2;
	std::string wrongAns3;

	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "ID")
		{
			id = atoi(argv[i]);
		}
		else if (std::string(azColName[i]) == "QUESTION")
		{
			question = argv[i];
		}
		else if (std::string(azColName[i]) == "ANS1")
		{
			ans = argv[i];
		}
		else if (std::string(azColName[i]) == "ANS2")
		{
			wrongAns = argv[i];
		}
		else if (std::string(azColName[i]) == "ANS3")
		{
			wrongAns2 = argv[i];
		}
		else if (std::string(azColName[i]) == "ANS4")
		{
			wrongAns3 = argv[i];
		}

	}
	questionList.push_back(Question(id, question, ans, wrongAns, wrongAns2, wrongAns3));

	return SQLITE_OK;
}

SqliteDataBase::SqliteDataBase() : db(nullptr), errMessage(nullptr)
{
	std::string dbFileName = "trivia.sqlite";
	int res = sqlite3_open(dbFileName.c_str(), &(this->db));
	if (res != SQLITE_OK) {
		this->db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		_exit(0);
	}

	std::cout << "Connected to DB Successfuly" << std::endl;

	std::string query = "CREATE TABLE USERS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, USERNAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);";

	res = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
		std::cout << errMessage << std::endl;

	query = "CREATE TABLE QUESTIONS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, QUESTION TEXT NOT NULL, ANSWER TEXT NOT NULL, WRONGANS TEXT NOT NULL, WRONGANS1 TEXT NOT NULL, WRONGANS2 TEXT NOT NULL);";
	res = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
		std::cout << errMessage << std::endl;
	
	query = "CREATE TABLE STATISTICS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, USERID INTEGER NOT NULL, HIGHSCORE INTEGER NOT NULL, SUMOFALLGAMESTIME INTEGER NOT NULL, NUMBEROFGAMESPLAYED INTEGER NOT NULL, SUMOFCORRECTANSWERS INTEGER NOT NULL, SUMOFANSWERS INTEGER NOT NULL, NUMOFCORRECTANSWERSINLASTGAME INTEGER NOT NULL, SUMOFTIMELASTGAMETOOK INTEGER NOT NULL, FOREIGN KEY (USERID) REFERENCES USERS(ID));";
	res = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
		std::cout << errMessage << std::endl;

	std::cout << "Created tables :)" << std::endl;

}

SqliteDataBase::~SqliteDataBase()
{
	sqlite3_close(this->db);
	db = nullptr;

	delete this->errMessage;
}

bool SqliteDataBase::doesUserExist(std::string username)
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

bool SqliteDataBase::doesPasswordMatch(std::string username, std::string pword)
{
	int res;

	std::string query = "SELECT * FROM USERS WHERE USERNAME = '" + username + "' AND PASSWORD = '" + pword + "';";
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

void SqliteDataBase::addNewUser(std::string username, std::string pword, std::string email)
{
	int res;

	std::string query = "INSERT INTO USERS (username, password, email) VALUES ('" + username + "', '" + pword + "', '" + email + "');";
	res = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
	}
}

std::list<Question> SqliteDataBase::getQuestions() 
{
	int res;

	questionList.clear();
	std::string query = "SELECT * FROM QUESTIONS";
	res = sqlite3_exec(db, query.c_str(), getQuestionCallback, &this->questionList, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
	}

	return this->questionList;
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string username)
{
	return 0.0f;
}
