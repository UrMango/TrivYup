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

inline void to_json(nlohmann::json& j, const PlayerResults& pl)
{
    j = { {"username", pl.username},
        {"correctAnswerCount", pl.correctAnswerCount},
        {"wrongAnswerCount", pl.wrongAnswerCount},
        {"averageAnswerTime", pl.averageAnswerTime} };
}

class Game
{
public:
    Game() {};
    Game(Room& room, std::vector<Question*> questions);
    std::string submitAnswer(LoggedUser* user, std::string answer);
    void removePlayer(LoggedUser* users);
    int getGameId() const;
    std::map<LoggedUser*, GameData*> getPlayers();
    Question* getQuestionForUser(LoggedUser* user, time_t time);
    bool getIsFinished();
    PlayerResults getPlayerResults(LoggedUser* user);
    std::vector<PlayerResults> getAllPlayerResults();

private:
    void newAvg(int newTime, LoggedUser* user);
	std::vector<Question*> m_questions;
	std::map<LoggedUser*, GameData*> m_players;
    bool isFinished = false;
    int m_gameId;
    time_t recieveTime;
};

