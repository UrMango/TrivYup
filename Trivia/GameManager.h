#pragma once
#include "IDatabase.h"
#include "Game.h";
#include "Room.h";
#include <iostream>;

class GameManager
{
private:
	IDatabase* m_database;
	std::vector<Game*> m_games;

public:
	GameManager(IDatabase* database) : m_database(database), m_games(NULL) {};
	~GameManager() {};

	Game* createGame(Room room);
	Game* getGame(int gameId);
	void updateStatistics(Game game);
	void deleteGame(int gameId);
	std::mutex _gamesMtx;

};

