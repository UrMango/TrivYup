#pragma once
#include "IDatabase.h"
#include "Game.h";
#include "Room.h";
#include <iostream>;

class GameManager
{
private:
	IDatabase* m_database;
	std::vector<Game> m_games;

public:
	Game createGame(Room room);
	void deleteGame(int gameId);
};

