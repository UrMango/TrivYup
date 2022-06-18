#include "Game.h"

Game::Game(Room& room, std::vector<Question*> questions) : m_questions(questions)
{
    for (int i = 0; i < room.getAllLoggedUsers().size(); i++) {
        struct GameData gamedata;
        gamedata.currectQuestion = questions[0];
        gamedata.averangeAnswerTime = 0;
        gamedata.correctAnswerCount = 0;
        gamedata.wrongAnswerCount = 0;
        gamedata.onGame = true;
        m_players.insert({&room.getAllLoggedUsers()[i], &gamedata});
    }
}

Question* Game::getQuestionForUser(LoggedUser* user)
{ 
    for (auto it : m_players)
    {
        if (it.first == user)
        {
            it.second->currectQuestion = m_questions[it.second->wrongAnswerCount + it.second->correctAnswerCount];
            return it.second->currectQuestion;
        }
    }
}

void Game::submitAnswer(LoggedUser* user, std::string answer)
{
    auto it = m_players.find(user);
    if (answer == it->second->currectQuestion->getCorrectAnswer())
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

