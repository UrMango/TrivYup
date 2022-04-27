#include "WSServer.h"

WSServer::WSServer() : ioc(1), acceptor(this->ioc, *(new tcp::endpoint(address, port))) // 1 is how many threads it should run together
{
	std::cout << "Server Started!" << std::endl;
	this->serve();
}

WSServer::~WSServer()
{
}

void WSServer::serve()
{
	std::cout << "Waiting for a socket connection..." << std::endl;

	while (true)
	{
		// wait for new socket connection
		tcp::socket socket(this->ioc);
		acceptor.accept();
		std::cout << "socket accepted" << std::endl;

		// the function that handle the conversation with the client
		std::thread clientThread(&WSServer::clientHandler, this, std::move(socket));
		clientThread.detach();
	}
}

void WSServer::clientHandler(tcp::socket socket)
{
	boost::beast::websocket::stream<tcp::socket> ws(std::move(socket));

	ws.accept();

	while (true)
	{
		boost::beast::flat_buffer buffer;
		ws.read(buffer);

		auto out = boost::beast::buffers_to_string(buffer.cdata());
		std::cout << "Client sent: " << out << std::endl;
	}
}
