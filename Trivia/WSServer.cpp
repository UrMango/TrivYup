#include "WSServer.h"
//#include <boost/beast.hpp>

WSServer::WSServer()
{
	std::cout << "Server Started!" << std::endl;

	this->serve();
}

WSServer::~WSServer()
{
}

void WSServer::serve()
{
	auto const address = net::ip::make_address("127.0.0.1");
	auto const port = static_cast<unsigned short>(std::atoi("8083"));

	net::io_context ioc{ 1 };

	tcp::acceptor acceptor{ ioc, {address, port} };

	std::thread commands(&WSServer::getCommands, this);

	while (true)
	{
		tcp::socket socket{ ioc };

		acceptor.accept(socket);


		std::thread(&WSServer::clientHandle, this, std::move(socket)).detach();
	}
}

void WSServer::clientHandle(tcp::socket socket) {
	// socket will be const - mutable should be used
	websocket::stream<tcp::socket> ws{ std::move(const_cast<tcp::socket&>(socket)) };

	// Accept the websocket handshake
	ws.accept();

	std::cout << "Connection succesfuly made!" << std::endl;

	this->m_clients.insert(std::pair<websocket::stream<tcp::socket>*, IRequestHandler*>(&ws, (IRequestHandler*)new LoginRequestHandler()));
	
	while (true)
	{
		try
		{
			beast::flat_buffer buffer;

			ws.write(net::buffer(JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("Error: you are a noob"))));

			// Read a message
			ws.read(buffer);

			auto out = beast::buffers_to_string(buffer.cdata());
			std::cout << out << std::endl;

			ws.write(buffer.data());
		}
		catch (beast::system_error const& se)
		{
			if (se.code() != websocket::error::closed)
			{
				std::cerr << "Error: " << se.code().message() << std::endl;
				break;
			}
		}
	}
}

void WSServer::getCommands()
{
	std::string command = "";
	while (command != "EXIT") {
		std::cin >> command;
		_exit(1);
	}
}
