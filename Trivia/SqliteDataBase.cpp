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
	Question& _question = *((Question*)data);

	int id = -1;
	std::string question;
	std::string ans;
	std::string wrongAns;
	std::string wrongAns2;
	std::string wrongAns3;

	for (int i = 0; i < argc; i++)
	{
		std::cout << azColName[i] << " : " << argv[i] << std::endl;
		if (std::string(azColName[i]) == "ID")
		{
			id = atoi(argv[i]);
		}
		else if (std::string(azColName[i]) == "QUESTION")
		{
			question = argv[i];
		}
		else if (std::string(azColName[i]) == "ANSWER")
		{
			ans = argv[i];
		}
		else if (std::string(azColName[i]) == "WRONGANS")
		{
			wrongAns = argv[i];
		}
		else if (std::string(azColName[i]) == "WRONGANS1")
		{
			wrongAns2 = argv[i];
		}
		else if (std::string(azColName[i]) == "WRONGANS2")
		{
			wrongAns3 = argv[i];
		}

	}
	_question = Question(id, question, ans, wrongAns, wrongAns2, wrongAns3);
	std::cout << _question.getId() << std::endl;

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

	std::cout << "sdasdsa" << std::endl;
	std::cout << azColName[0] << std::endl;
	if (std::string(azColName[0]) == "NUMOFCORRECTANSWERS")
	{
		std::cout << azColName[0] << std::endl;
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

int getNumOfPlayerGamesCallback(void* data, int argc, char** argv, char** azColName)
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

SqliteDataBase::SqliteDataBase() : db(nullptr), errMessage(nullptr), floatReturn(0.f), numReturn(0), question(Question(0, "", "", "", "", ""))
{
	std::string dbFileName = "trivia.sqlite";
	int res = sqlite3_open(dbFileName.c_str(), &(this->db));
	if (res != SQLITE_OK) {
		this->db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		_exit(0);
	}

	std::cout << "Connected to DB Successfuly" << std::endl;

	std::string* query = new string();
	*query = "CREATE TABLE USERS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, USERNAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, EMAIL TEXT NOT NULL);";

	res = sqlite3_exec(db, (*query).c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
		std::cout << errMessage << std::endl;

	*query = "CREATE TABLE QUESTIONS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, QUESTION TEXT NOT NULL, ANSWER TEXT NOT NULL, WRONGANS TEXT NOT NULL, WRONGANS1 TEXT NOT NULL, WRONGANS2 TEXT NOT NULL);";
	res = sqlite3_exec(db, (*query).c_str(), nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
		std::cout << errMessage << std::endl;
	
	*query = "CREATE TABLE STATISTICS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, USERID INTEGER NOT NULL, AVERAGEANSWERTIME INTEGER NOT NULL, NUMBEROFGAMESPLAYED INTEGER NOT NULL, NUMOFCORRECTANSWERS INTEGER NOT NULL, NUMOFANSWERS INTEGER NOT NULL, FOREIGN KEY (USERID) REFERENCES USERS(ID));";
	res = sqlite3_exec(db, (*query).c_str(), nullptr, nullptr, &errMessage);
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

	std::string* query = new string();
	*query = "SELECT * FROM USERS WHERE USERNAME = '" + username + "';";

	try{
		res = sqlite3_exec(db, (*query).c_str(), countSelectCallback, nullptr, &errMessage);
	}
	catch (...){
		std::cout << "Catch an error" << '\n';
	}

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

	std::string* query = new string();
	*query = "SELECT * FROM USERS WHERE USERNAME = '" + username + "' AND PASSWORD = '" + pword + "';";

	try {
		res = sqlite3_exec(db, (*query).c_str(), countSelectCallback, nullptr, &errMessage);
	}
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}

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

	std::string* query = new string();
	*query = "INSERT INTO USERS (username, password, email) VALUES ('" + username + "', '" + pword + "', '" + email + "');";
	_dataBasetx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
	try {
		res = sqlite3_exec(db, (*query).c_str(), nullptr, nullptr, &errMessage);
	}
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}
	_dataBasetx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
	}
	
	*query = "INSERT INTO STATISTICS (userid, averageanswertime, numberofgamesplayed, numofcorrectanswers, numofanswers) VALUES(" + std::to_string(getUserId(username)) + ", 0.0, 0, 0, 0);";
	_dataBasetx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
	try {
		res = sqlite3_exec(db, (*query).c_str(), nullptr, nullptr, &errMessage);
	}
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}
	_dataBasetx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
	}
}

int SqliteDataBase::getUserId(std::string username)
{
	int res, id;

	std::string* query = new string();
	*query = "SELECT id from USERS WHERE username == '" + username + "';";
	try {
		res = sqlite3_exec(db, (*query).c_str(), getID, &this->numReturn, &errMessage);
	}
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}

	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return -1;
	}
	id = this->numReturn;

	return id;
}

std::vector<Question> SqliteDataBase::getQuestions(int numQuestions)
{
	int res;
	bool ifAvailable = false;
	int randomId = -1;
	const int QUESTION_COUNT = 400;
	std::vector<Question> questionsList;

	for (int i = 0; i < numQuestions; i++)
	{
		ifAvailable = false;
		while (!ifAvailable)
		{
			ifAvailable = true;
			srand((unsigned)time(0));
			randomId = (rand() % QUESTION_COUNT) + 1;

			for (auto it : questionsList)
			{
				if (it.getId() == randomId) {
					ifAvailable = false;
					break;
				}
			}
		}

		std::string* query = new string();
		*query = "SELECT * FROM QUESTIONS WHERE id = " + std::to_string(randomId) + ";";

		try {
			res = sqlite3_exec(db, (*query).c_str(), getQuestionCallback, &this->question, &errMessage);
		}
		catch (...) {
			std::cout << "Catch an error" << '\n';
		}

		if (res != SQLITE_OK)
		{
			std::cout << errMessage << std::endl;
		}
		if (&this->question)
			questionsList.push_back(this->question);
	}

	return questionsList;
}

void SqliteDataBase::updateStatistics(std::string username, GameData playerGameData)
{
	int res;
	std::string* query2 = new string();

	float averageAnswerTime = (this->getPlayerAverageAnswerTime(username) + playerGameData.averangeAnswerTime) / 2;
	int numberOfGamesPlayed= this->getNumOfPlayerGames(username) + 1;
	int numberOfCorrectAnswer = this->getNumOfCorrectAnswers(username) + playerGameData.correctAnswerCount;
	int numberOfAnswers = this->getNumOfTotalAnswers(username);
	numberOfAnswers += playerGameData.correctAnswerCount + playerGameData.wrongAnswerCount;

	*query2 = "UPDATE STATISTICS SET averageanswertime = " + std::to_string(averageAnswerTime) + ", numberofgamesplayed = " + std::to_string(numberOfGamesPlayed) + ", numofcorrectanswers = " + std::to_string(numberOfCorrectAnswer) + ", numofanswers = " + std::to_string(numberOfAnswers) + " WHERE userid = " + std::to_string(getUserId(username)) + ";";
	_dataBasetx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
	try {
		res = sqlite3_exec(db, (*query2).c_str(), nullptr, nullptr, &errMessage);
	}
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}
	_dataBasetx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked

	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
	}
}

float SqliteDataBase::getPlayerAverageAnswerTime(std::string username)
{
	int res, id;
	id = getUserId(username);

	std::string* query = new string();
	*query = "SELECT AVERAGEANSWERTIME from STATISTICS WHERE userid = ";
	*query += std::to_string(id) + ";";
	try {
		res = sqlite3_exec(db, (*query).c_str(), getAverageAnswerTime, &this->floatReturn, &errMessage);
	}
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return -1.f;
	}

	return this->floatReturn;
}

int SqliteDataBase::getNumOfCorrectAnswers(std::string username)
{
	int res = -1, id;
	id = getUserId(username);

	std::string* query = new string();
	*query = "SELECT NUMOFCORRECTANSWERS from STATISTICS WHERE userid = ";
	*query += std::to_string(id) + ";";
	try {
		res = sqlite3_exec(db, (*query).c_str(), getNumOfCorrectAnswersCallback, &this->numReturn, &errMessage);
	}
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return -1;
	}
	return this->numReturn;
}

int SqliteDataBase::getNumOfTotalAnswers(std::string username)
{
	int res = -1, id;
	id = getUserId(username);

	std::string* query = new string();
	*query = "SELECT NUMOFANSWERS FROM STATISTICS WHERE userid = " + std::to_string(id) + ";";
	try {
		res = sqlite3_exec(db, (*query).c_str(), getNumOfTotalAnswersCallback, &this->numReturn, &errMessage);
	}
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return -1;
	}

	return this->numReturn;
}

int SqliteDataBase::getNumOfPlayerGames(std::string username)
{
	int res = -1, id;
	id = this->getUserId(username);

	std::string* query = new string();
	*query = "SELECT NUMBEROFGAMESPLAYED from STATISTICS WHERE userid = ";
	*query += std::to_string(id) + ";";
	try {
		res = sqlite3_exec(db, (*query).c_str(), getNumOfPlayerGamesCallback, &this->numReturn, &errMessage);
	}
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}
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

	std::string* query = new string();
	*query = "SELECT * from USERS;";
	int res;
	try {
		res = sqlite3_exec(db, (*query).c_str(), getUsersList, &usersList, &errMessage);
	}
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}
	if (res != SQLITE_OK)
	{
		std::cout << errMessage << std::endl;
		return std::vector<std::pair<std::string, int>>();
	}

	int score;
	for (int i = 0; i < usersList.size(); i++)
	{
		int correct = SqliteDataBase::getNumOfCorrectAnswers(usersList[i].second);
		int all = SqliteDataBase::getNumOfPlayerGames(usersList[i].second);
		float averageTime = SqliteDataBase::getPlayerAverageAnswerTime(usersList[i].second);
		try {
			score = 1000 * (all / (correct / averageTime));
		}
		catch (...) {
			std::cout << "Catch an error" << '\n';
		}
		highscoreList.push_back(std::pair<std::string, int>(usersList[i].second, score));
	}

	std::sort(highscoreList.begin(), highscoreList.end(), [](auto& left, auto& right) {
		return left.second > right.second;
	});
	return highscoreList;
}
