#include "GameManager.h"

Game& GameManager::createGame(Room room)
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

void GameManager::deleteGame(int gameId)
{
}
