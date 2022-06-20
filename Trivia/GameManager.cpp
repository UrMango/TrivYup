#include "GameManager.h"

Game& GameManager::createGame(Room room)
{
    std::vector<Question*> questions;
    std::list<Question> questionList = m_database->getQuestions(room.getRoomData().numOfQuestionsInGame);

    for (auto it : questionList)
    {
        Question* question = new Question(it.getId(), it.getQuestion(), it.getCorrectAnswer(), it.getPossibleAnswers()[1], it.getPossibleAnswers()[2], it.getPossibleAnswers()[3]);
        questions.push_back(question);
    }

    Game game = *(new Game(room, questions));
    this->m_games.push_back(game);

    return game;
}

Game* GameManager::getGame(int gameId)
{
    for (auto it : this->m_games)
    {
        if(it.getGameId() == gameId)
            return &it;
    }
    return nullptr;
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
    int i = 0;
    for (auto it : this->m_games )
    {
        if (it.getGameId() == gameId) 
        {
            updateStatistics(it);
            this->m_games.erase(this->m_games.begin() + i); 
            return;
        }
        i++;
    }
}
