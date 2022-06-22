#include "Game.h"

Game::Game(Room& room, std::vector<Question*> questions) : m_questions(questions), m_gameId(room.getRoomData().id)
{
    for (int i = 0; i < room.getAllLoggedUsers()->size(); i++) {
        struct GameData* gamedata = new GameData();
        gamedata->currectQuestion = questions[0];
        gamedata->averangeAnswerTime = 1;
        gamedata->correctAnswerCount = 0;
        gamedata->wrongAnswerCount = 0;
        gamedata->onGame = true;
        gamedata->hasAnswered = false;

        recieveTime = time(0);
        LoggedUser* user = (*room.getAllLoggedUsers())[i];
        m_players.insert({user, gamedata});
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
                return nullptr;
            }
            user->setMsgTime(time);
            it.second->currectQuestion = m_questions[it.second->wrongAnswerCount + it.second->correctAnswerCount];
            it.second->hasAnswered = false;
            return it.second->currectQuestion;
        }
    }
    return nullptr;
}

std::map<LoggedUser*, GameData*> Game::getPlayers()
{
    return this->m_players;
}

void Game::newAvg(float newTime, LoggedUser* user)
{
    auto it = m_players.find(user);
    if (it != m_players.end()) {
        int numQuestions = it->second->wrongAnswerCount + it->second->correctAnswerCount; 
            if (numQuestions == 0)
                it->second->averangeAnswerTime = newTime;
            else
                it->second->averangeAnswerTime = ((1 / (float)(numQuestions + 1)) * (numQuestions)*it->second->averangeAnswerTime) + (newTime * (1 / (float)(numQuestions + 1)));

    }
   // printf("\n new avg %f\n", it->second->averangeAnswerTime);
}

std::string Game::submitAnswer(LoggedUser* user, std::string answer) 
{
    recieveTime = time(0);
    time(&recieveTime);
    float newTime = difftime(recieveTime , user->getMsgTime());
    //std::cout << "Time required = " << difftime(recieveTime, user->getMsgTime()) << " seconds";

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

    it->second->hasAnswered = true;

    bool everyoneAnswerd = true;
    for (auto pl : m_players)
    {
        if (pl.second->correctAnswerCount + pl.second->wrongAnswerCount < it->second->correctAnswerCount + it->second->wrongAnswerCount)
        {
            everyoneAnswerd = false;
            break;
        }
    }
    this->isEveryoneAnswerd = everyoneAnswerd;
    if (this->isEveryoneAnswerd && it->second->correctAnswerCount + it->second->wrongAnswerCount == this->m_questions.size()) { this->isFinished = true; }
    return it->second->currectQuestion->getCorrectAnswer();
}

GameData* Game::getPlayerData(LoggedUser* user)
{
    for (auto it : m_players)
    {
        if (it.first == user)
        {
            return it.second;
        }
    }
    return nullptr;
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

bool compareByScore(const PlayerResults& a, const PlayerResults& b)
{
    return a.score > b.score;
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
        playerResults.score = 1000 * ((it.second->correctAnswerCount) / (it.second->averangeAnswerTime));
        results.push_back(playerResults);
    }
    std::sort(results.begin(), results.end(), compareByScore);

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
