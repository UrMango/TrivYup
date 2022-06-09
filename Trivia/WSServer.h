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
	void build_receive_message(const RequestInfo request, websocket::stream<tcp::socket> ws);
	void getCommands();
	void serve();
	void clientHandle(tcp::socket socket);
	std::map<websocket::stream<tcp::socket>*, IRequestHandler*> m_clients;
	IDatabase* m_database;
	time_t _time; 

};
