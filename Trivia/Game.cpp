#include "Game.h"

Game::Game(Room& room, std::vector<Question*> questions) : m_questions(questions), m_gameId(room.getRoomData().id)
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

Question* Game::getQuestionForUser(LoggedUser* user, time_t time)
{ 
    for (auto it : m_players)
    {
        if (it.first == user)
        {
            if (m_questions.size() == (it.second->wrongAnswerCount + it.second->correctAnswerCount))
            {
                return NULL;
            }
            user->setMsgTime(time);
            it.second->currectQuestion = m_questions[it.second->wrongAnswerCount + it.second->correctAnswerCount];
            return it.second->currectQuestion;
        }
    }
}

std::map<LoggedUser*, GameData*> Game::getPlayers()
{
    return this->m_players;
}

void Game::newAvg(int newTime, LoggedUser* user)
{
    auto it = m_players.find(user);
    int numQuestions = it->second->wrongAnswerCount + it->second->correctAnswerCount;
    it->second->averangeAnswerTime = ((1 / numQuestions + 1) * numQuestions * it->second->averangeAnswerTime) + (newTime * (1 / numQuestions + 1));
}

std::string Game::submitAnswer(LoggedUser* user, std::string answer) 
{
    time(&recieveTime);
    int newTime = difftime(recieveTime, user->getMsgTime());
    this->newAvg(newTime, user);
    auto it = m_players.find(user);
    if (answer == it->second->currectQuestion->getCorrectAnswer())
    {
        it->second->correctAnswerCount++;
    }
    else
    {
        it->second->wrongAnswerCount++;
    }

    bool everyoneAnswerd = true;
    for (auto pl : m_players)
    {
        if (pl.second->correctAnswerCount + pl.second->wrongAnswerCount != it->second->correctAnswerCount + it->second->wrongAnswerCount)
        {
            everyoneAnswerd = false;
            break;
        }
    }
    this->isEveryoneAnswerd = everyoneAnswerd;
    if (this->isEveryoneAnswerd && it->second->correctAnswerCount + it->second->wrongAnswerCount == this->m_questions.size()) { this->isFinished = true; }
    return it->second->currectQuestion->getCorrectAnswer();
}

void Game::removePlayer(LoggedUser* users)
{
    for (auto it : m_players)
    {
        if (it.first == users)
        {
            it.second->onGame = false;
            break;
        }
    }
}

bool Game::getIsFinished()
{
    return this->isFinished;
}

bool Game::getIsEveryoneAnswerd()
{
    return this->isEveryoneAnswerd;
}

int Game::getGameId() const
{
    return this->m_gameId;
}

std::vector<PlayerResults> Game::getAllPlayerResults()
{
    std::vector<PlayerResults> results;
    for (auto it : m_players)
    {
        PlayerResults playerResults;
        playerResults.averageAnswerTime = it.second->averangeAnswerTime;
        playerResults.correctAnswerCount = it.second->correctAnswerCount;
        playerResults.username = it.first->getUsername();
        playerResults.wrongAnswerCount = it.second->wrongAnswerCount;
        results.push_back(playerResults);
    }
    return results;
}

PlayerResults Game::getPlayerResults(LoggedUser* user)
{
    auto it = m_players.find(user);
    PlayerResults playerResults;
    playerResults.averageAnswerTime = it->second->averangeAnswerTime;
    playerResults.correctAnswerCount = it->second->correctAnswerCount;
    playerResults.username = user->getUsername();
    playerResults.wrongAnswerCount = it->second->wrongAnswerCount;
    return playerResults;
}
