#pragma once

#include <string>
#include <WinSock2.h>
#include <boost/beast.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

#include "IRequestHandler.h"
using tcp = boost::asio::ip::tcp;
class IRequestHandler;

enum MessageType 
{
	MT_CLIENT_LOG_IN = 200,
	MT_CLIENT_SIGN_UP = 204,

	//MT_CLIENT_FINISH = 207,
	//MT_CLIENT_EXIT = 208,
	//MT_SERVER_UPDATE = 101,
};

struct RequestInfo {
	int msgCode = 0;
	std::string msgTime = "";
	std::string msg = "";
};

struct RequestResult {
	std::string msg;
	IRequestHandler* newHandler;
};

struct RoomData
{
	unsigned int id = 0;
	std::string name = "";
	unsigned int maxPlayers = 0;
	unsigned int numOfQuestionsInGame = 0;
	unsigned int timePerQuestion = 0;
	unsigned int isActive = 0; //0-not active, 1-active
};