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

