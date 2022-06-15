#include "Game.h"

Game::Game(LoggedUser* User)
{
    Question* qeu = m_questions[0];
    struct GameData gamedata;
    gamedata.averangeAnswerTime = 0;
    gamedata.correctAnswerCount = 0;
    gamedata.currentQuestion = qeu;
    gamedata.wrongAnswerCount = 0;
    m_players.insert({ User, gamedata });
}

Question* Game::getQuestionForUser(LoggedUser* users)
{
    auto it = m_players.find(users);
    int place = it->second.wrongAnswerCount + it->second.correctAnswerCount;
    return m_questions[place];
}