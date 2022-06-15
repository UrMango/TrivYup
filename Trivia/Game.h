#pragma once
#include <string>
#include "Helper.h"
#include <vector>
#include <map>
#include "Question.h"
#include "LoggedUser.h"

struct GameData
{
	Question* currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
    float averangeAnswerTime;
};

class Game
{
public:
    Game(LoggedUser* User);
    void submitAnswer(LoggedUser* users, int answeriD);
    void removePlayer(LoggedUser* users);
    int getGameId() const;
    Question* getQuestionForUser(struct LoggedUser* users);

private:
	std::vector<Question*> m_questions;
	std::map<LoggedUser*, GameData> m_players;
    int m_gameId;
};

