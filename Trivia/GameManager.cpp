#include "GameManager.h"

Game GameManager::createGame(Room room)
{
    std::vector<Question*> questions;
    std::list<Question> questionList = m_database->getQuestions(room.getRoomData().numOfQuestionsInGame);

    for (auto it : questionList)
    {
        questions.push_back(&it);
    }

    Game game = *(new Game(room, questions));
    this->m_games.push_back(game);

    return game;
}

void GameManager::updateStatistics(Game game)
{
    for (auto it : game.getPlayers())
    {
        this->m_database->updateStatistics(it.first->getUsername(), *it.second);
    }
}

void GameManager::deleteGame(int gameId)
{
    for (auto it : this->m_games )
    {
        if (it.getGameId() == gameId) 
        {
            updateStatistics(it);
            std::remove(this->m_games.begin(), this->m_games.end(), it);
            return;
        }
    }
}
