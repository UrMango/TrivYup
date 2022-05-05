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

	while (true)
	{
		tcp::socket socket{ ioc };

		acceptor.accept(socket);

		std::thread{ std::bind([q{std::move(socket)}]()
		{
			// socket will be const - mutable should be used
			websocket::stream<tcp::socket> ws{ std::move(const_cast<tcp::socket&>(q)) };

			// Accept the websocket handshake
			ws.accept();

			while (true)
			{
				try
				{
					beast::flat_buffer buffer;

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
		}) }.detach();
	}
}
