#include "GameManager.h"

Game* GameManager::createGame(Room room)
{
    std::vector<Question*> questions;
    std::vector<Question> questionList = m_database->getQuestions(room.getRoomData().numOfQuestionsInGame);

    for (int i = 0; i < questionList.size(); i++)
    {
        printf("ans = %s", questionList[i].getPossibleAnswers()[0]);
        Question* question = new Question(questionList[i].getId(), questionList[i].getQuestion(), questionList[i].getPossibleAnswers()[1], questionList[i].getPossibleAnswers()[2], questionList[i].getPossibleAnswers()[3], questionList[i].getPossibleAnswers()[4]);
        questions.push_back(question);
    }


    Game* game = new Game(room, questions);
    this->m_games.push_back(game);

    return this->m_games[this->m_games.size() - 1];
}

Game* GameManager::getGame(int gameId)
{
    for (auto it : this->m_games)
    {
        if (it->getGameId() == gameId)
            return it;
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
    for (auto it : this->m_games)
    {
        if (it->getGameId() == gameId)
        {
            updateStatistics(*it);
            this->m_games.erase(this->m_games.begin() + i);
            return;
        }
        i++;
    }
}
