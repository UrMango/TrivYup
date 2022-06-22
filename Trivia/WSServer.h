#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <map>
#include "Helper.h"
#include <ctime>
#include "SqliteDataBase.h"
#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "ErrorResponse.h"
#include "IRequestHandler.h"
#include "Communicator.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class WSServer
{
public:
	WSServer();
	~WSServer();

private:
	void run();
	IDatabase* m_database;
	Communicator* m_communicator;
	RequestHandlerFactory* m_handlerFactory;
	time_t _time; 
};

