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
#include "RequestHandlerFactory.h"
#include "RoomAdminRequestHandler.h"


namespace beast = boost::beast;
namespace http = beast::http;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory, IDatabase& database);
	void startHandleRequests();
	~Communicator();

private:
	void getCommands();
	void handleNewClient(tcp::socket socket);
	std::map<websocket::stream<tcp::socket>*, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;
	IDatabase& m_database;
	time_t _time;
	std::mutex _clientsMtx;

};
