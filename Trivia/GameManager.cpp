#include "GameManager.h"


//***********************************************************************************************
//the func create a game
//***********************************************************************************************
Game* GameManager::createGame(Room room)
{
    std::vector<Question*> questions;
    std::vector<Question> questionList = m_database->getQuestions(room.getRoomData().numOfQuestionsInGame);

    for (int i = 0; i < questionList.size(); i++)
    {
        Question* question = new Question(questionList[i].getId(), questionList[i].getQuestion(), questionList[i].getPossibleAnswers()[1], questionList[i].getPossibleAnswers()[2], questionList[i].getPossibleAnswers()[3], questionList[i].getPossibleAnswers()[4]);
        questions.push_back(question);
    }

    Game* game = new Game(room, questions);
    _gamesMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
        this->m_games.push_back(game);
        Game* res = this->m_games[this->m_games.size() - 1];
    _gamesMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
    return res;
}


//***********************************************************************************************
//the func return a game according id
//***********************************************************************************************
Game* GameManager::getGame(int gameId)
{
        for (auto it : this->m_games)
        {
            if (it->getGameId() == gameId)
                return it;
        }
    return nullptr;
}


//***********************************************************************************************
//the func udate the Statistics according game result
//***********************************************************************************************
void GameManager::updateStatistics(Game game)
{
    for (auto it : game.getPlayers())
    {
        this->m_database->updateStatistics(it.first->getUsername(), *it.second);
    }
}

//***********************************************************************************************
//the func delete a game
//***********************************************************************************************
void GameManager::deleteGame(int gameId)
{
    int i = 0;
    _gamesMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
        for (auto it : this->m_games)
        {
            if (it->getGameId() == gameId)
            {
                updateStatistics(*it);
                this->m_games.erase(this->m_games.begin() + i);
                _gamesMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
                return;
            }
            i++;
        }
    _gamesMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
}
