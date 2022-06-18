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
	Question* _question = ((Question*)data);

	int id = -1;
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
	_question = new Question(id, question, ans, wrongAns, wrongAns2, wrongAns3);

	return SQLITE_OK;
}

int getID(void* data, int argc, char** argv, char** azColName)
{
	int* numReturn = ((int*)data);

	if (std::string(azColName[0]) == "ID")
	{
		*numReturn = atoi(argv[0]);
	}
	else
	{
		return SQLITE_ERROR;
	}

	return SQLITE_OK;
}

int getAverageAnswerTime(void* data, int argc, char** argv, char** azColName)
{
	float* floatReturn = ((float*)data);

	if (std::string(azColName[0]) == "AVERAGEANSWERTIME")
	{
		*floatReturn = std::stof(argv[0]);
	}
	else
	{
		return SQLITE_ERROR;
	}

	return SQLITE_OK;
}

int getNumOfCorrectAnswersCallback(void* data, int argc, char** argv, char** azColName)
{
	int* numReturn = ((int*)data);

	if (std::string(azColName[0]) == "NUMOFCORRECTANSWERS")
	{
		*numReturn = atoi(argv[0]);
	}
	else
	{
		return SQLITE_ERROR;
	}

	return SQLITE_OK;
}

int getNumOfTotalAnswersCallback(void* data, int argc, char** argv, char** azColName)
{
	int* numReturn = ((int*)data);

	if (std::string(azColName[0]) == "NUMBEROFGAMESPLAYED")
	{
		*numReturn = atoi(argv[0]);
	}
	else
	{
		return SQLITE_ERROR;
	}

	return SQLITE_OK;
}

int getNumOfPlayerGamesCallback(void* data, int argc, char** argv, char** azColName)
{
	int* numReturn = ((int*)data);

	if (std::string(azColName[0]) == "NUMOFANSWERS")
	{
		*numReturn = atoi(argv[0]);
	}
	else
	{
		return SQLITE_ERROR;
	}

	return SQLITE_OK;
}

int getUsersList(void* data, int argc, char** argv, char** azColName)
{
	std::vector<std::pair<int, std::string>>* usersList = ((std::vector<std::pair<int, std::string>>*)data);

	int id;
	std::string username;

	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "ID")
		{
			id = atoi(argv[i]);
		}
		else if (std::string(azColName[i]) == "USERNAME")
		{
			username = argv[i];
		}
	}

	usersList->push_back(std::pair<int, std::string>(id, username));

	return SQLITE_OK;
}

SqliteDataBase::SqliteDataBase() : db(nullptr), errMessage(nullptr), floatReturn(0.f), numReturn(0)
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
	
	query = "CREATE TABLE STATISTICS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, USERID INTEGER NOT NULL, AVERAGEANSWERTIME INTEGER NOT NULL, NUMBEROFGAMESPLAYED INTEGER NOT NULL, NUMOFCORRECTANSWERS INTEGER NOT NULL, NUMOFANSWERS INTEGER NOT NULL, FOREIGN KEY (USERID) REFERENCES USERS(ID));";
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

std::list<Question> SqliteDataBase::getQuestions(int numQuestions)
{
	int res;
	bool found = true;
	int randomId = -1;
	const int QUESTION_COUNT = 400;

	std::list<Question> questionsList;

	for (int i = 0; i < numQuestions; i++)
	{
		while (!found)
		{
			found = true;
			srand((unsigned)time(0));
			randomId = (rand() % QUESTION_COUNT) + 1;

			for (auto it : questionsList)
			{
				if (it.getId() == randomId) {
					found = false;
					break;
				}
			}
		}

		std::string query = "SELECT * FROM QUESTIONS WHERE id = " + randomId;
		query += ";";
		res = sqlite3_exec(db, query.c_str(), getQuestionCallback, this->question, &errMessage);
		if (res != SQLITE_OK)
		{
			std::cout << errMessage << std::endl;
		}
		questionsList.push_back(*this->question);
	}

	return questionsList;
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string username)
{
	int res;
	int id;

	std::string query = "SELECT id from USERS WHERE username == '" + username + "';";
	res = sqlite3_exec(db, query.c_str(), getID, &this->numReturn, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return -1.f;
	}
	id = this->numReturn;

	query = "SELECT AVERAGEANSWERTIME from STATISTICS WHERE userid = ";
	query += id + ";";
	res = sqlite3_exec(db, query.c_str(), getAverageAnswerTime, &this->floatReturn, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return -1.f;
	}

	return this->floatReturn;
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string username)
{
	int res;
	int id;

	std::string query = "SELECT id from USERS WHERE username == '" + username + "';";
	res = sqlite3_exec(db, query.c_str(), getID, &this->numReturn, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return -1;
	}
	id = this->numReturn;

	query = "SELECT NUMOFCORRECTANSWERS from STATISTICS WHERE userid = ";
	query += id + ";";
	res = sqlite3_exec(db, query.c_str(), getNumOfCorrectAnswersCallback, &this->numReturn, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return -1;
	}

	return this->numReturn;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string username)
{
	int res;
	int id;

	std::string query = "SELECT id from USERS WHERE username == '" + username + "';";
	res = sqlite3_exec(db, query.c_str(), getID, &this->numReturn, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return -1;
	}
	id = this->numReturn;

	query = "SELECT NUMOFANSWERS from STATISTICS WHERE userid = ";
	query += id + ";";
	res = sqlite3_exec(db, query.c_str(), getNumOfTotalAnswersCallback, &this->numReturn, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return -1;
	}

	return this->numReturn;
}

int SqliteDataBase::getNumOfPlayerGames(std::string username)
{
	int res;
	int id;

	std::string query = "SELECT id from USERS WHERE username == '" + username + "';";
	res = sqlite3_exec(db, query.c_str(), getID, &this->numReturn, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return -1;
	}
	id = this->numReturn;

	query = "SELECT NUMBEROFGAMESPLAYED from STATISTICS WHERE userid = ";
	query += id + ";";
	res = sqlite3_exec(db, query.c_str(), getNumOfTotalAnswersCallback, &this->numReturn, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return -1;
	}

	return this->numReturn;
}

std::vector<std::pair<std::string, int>> SqliteDataBase::getHighscores()
{

	std::vector<std::pair<int, std::string>> usersList;

	std::vector<std::pair<std::string, int>> highscoreList;

	/*std::pair<std::string, int> first;
	std::pair<std::string, int> second;
	std::pair<std::string, int> third;*/

	std::string query = "SELECT * from USERS;";
	int res = sqlite3_exec(db, query.c_str(), getUsersList, &usersList, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return std::vector<std::pair<std::string, int>>();
	}

	for (int i = 0; i < usersList.size(); i++)
	{
		int total = SqliteDataBase::getNumOfTotalAnswers(usersList[i].second);
		int correct = SqliteDataBase::getNumOfCorrectAnswers(usersList[i].second);
		int all = SqliteDataBase::getNumOfPlayerGames(usersList[i].second);
		float averageTime = SqliteDataBase::getPlayerAverageAnswerTime(usersList[i].second);

		// function: Total / (Wrong * average answer time)
		int score = total / ((all - correct) * averageTime);

		highscoreList.push_back(std::pair<std::string, int>(usersList[i].second, score));

		/*if (score > first.second) {
			third = second;
			second = first;
			first = std::pair<std::string, int>(usersList[i].second, score);
		}
		else if (score > second.second) {
			third = second;
			second = std::pair<std::string, int>(usersList[i].second, score);
		} else if (score > third.second) {
			third = second;
		}*/
	}

	std::sort(highscoreList.begin(), highscoreList.end(), [](auto& left, auto& right) {
		return left.second < right.second;
	});

	return highscoreList;
}
