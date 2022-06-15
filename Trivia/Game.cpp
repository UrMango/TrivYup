#include "Game.h"

Game::Game(Room& room)
{
    for (int i = 0; i < room.getAllLoggedUsers().size(); i++) {
        struct GameData gamedata;
        gamedata.currentQuestion = m_questions[0];
        gamedata.averangeAnswerTime = 0;
        gamedata.correctAnswerCount = 0;
        gamedata.wrongAnswerCount = 0;
        gamedata.onGame = true;
        m_players.insert({&room.getAllLoggedUsers()[i], &gamedata});
    }
}

Question* Game::getQuestionForUser(LoggedUser* users)
{ 
    for (auto it : m_players)
    {
        if (it.first == users)
        {
            return m_questions[it.second->wrongAnswerCount + it.second->correctAnswerCount];
        }
    }
}

void Game::submitAnswer(LoggedUser* users, std::string answer)
{
    auto it = m_players.find(users);
    if (answer == it->second->currentQuestion->getCorrentAnswer())
    {
        it->second->correctAnswerCount++;
    }
    else
    {
        it->second->wrongAnswerCount++;
    }
}

void Game::removePlayer(LoggedUser* users)
{
    for (auto it : m_players)
    {
        if (it.first == users)
        {
            it.second->onGame = false;
        }
    }
}

int Game::getGameId() const
{
    return this->m_gameId;
}

