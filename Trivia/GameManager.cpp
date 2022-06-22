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
    _gamesMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
        this->m_games.push_back(game);
        Game* res = this->m_games[this->m_games.size() - 1];
    _gamesMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
    return res;
}

Game* GameManager::getGame(int gameId)
{
    _gamesMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
        for (auto it : this->m_games)
        {
            if (it->getGameId() == gameId)
                _gamesMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
                return it;
        }
    _gamesMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
    return nullptr;
}

void GameManager::updateStatistics(Game game)
{
    _gamesMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
        for (auto it : game.getPlayers())
        {
            this->m_database->updateStatistics(it.first->getUsername(), *it.second);
        }
    _gamesMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
}

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
