#pragma once
#include <string>
#include <vector>
#include <map>
#include "Question.h"

#include "Helper.h"

#include "LoggedUser.h"
#include "Room.h"
struct GameData
{
	Question* currectQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
    float averangeAnswerTime;
    bool onGame;
};
struct PlayerResults
{
    std::string username;
    unsigned int correctAnswerCount;
    unsigned int wrongAnswerCount;
    unsigned int averageAnswerTime;
};

class Game
{
public:
    Game(Room& room, std::vector<Question*> questions);
    void submitAnswer(LoggedUser* user, std::string answer);
    void removePlayer(LoggedUser* users);
    int getGameId() const;
    Question* getQuestionForUser(LoggedUser* user);

private:
	std::vector<Question*> m_questions;
	std::map<LoggedUser*, GameData*> m_players;
    int m_gameId;
};

