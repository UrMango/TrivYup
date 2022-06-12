#pragma once

#include <string>
#include <WinSock2.h>
#include <boost/beast.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <json.hpp>

#include "IRequestHandler.h"
using tcp = boost::asio::ip::tcp;
class IRequestHandler;

enum MessageType
{
	MT_CLIENT_LOG_IN = 200,
	MT_CLIENT_SIGN_UP = 204,
	CREATE_ROOM = 205,
	GET_ROOMS = 206,
	GET_PLAYERS_IN_ROOM = 207,
	JOIN_ROOM = 208,
	GET_STATISTICS = 209,
	LOG_OUT = 210,
	HIGH_SCORE = 211,
	GET_PERSONAL_STATS = 212,
	CLOSE_ROOM = 213,
	START_GAME = 214,
	GET_ROOM_STATE = 215,
	LEAVE_ROOM = 216
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

