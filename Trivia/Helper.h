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
	CREATE_ROOM = 1,
	GET_ROOMS = 2,
	GET_PLAYERS_IN_ROOM = 3,
	JOIN_ROOM = 4,
	GET_STATISTICS = 5,
	LOG_OUT = 6,
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