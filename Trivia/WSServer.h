
#pragma once
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <map>

#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "JsonResponsePacketSerializer.h"

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
	void serve();
	void clientHandle(tcp::socket socket);
	void getCommands();
		
	std::map<websocket::stream<tcp::socket>*, IRequestHandler*> m_clients;

	/*const boost::asio::ip::address address = boost::asio::ip::make_address("127.0.0.1");
	const unsigned short port = 8080;*/
private:

	///* io_context gets and makes the server pc do a connection operation */
	//boost::asio::io_context ioc;

	//tcp::acceptor acceptor;

};
