#pragma once
#include <string>
#include "Helper.h"
#include <vector>
#include <map>
#include "Question.h"
#include "LoggedUser.h"
#include "Room.h"

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
    Game(Room& room);
    void submitAnswer(LoggedUser* users, std::string answer);
    void removePlayer(LoggedUser users);
    int getGameId() const;
    Question* getQuestionForUser(LoggedUser* users);

private:
	std::vector<Question*> m_questions;
	std::map<LoggedUser*, GameData*> m_players;
    int m_gameId;
};

