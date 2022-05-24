#include "WSServer.h"

WSServer::WSServer()
{
	std::cout << "Server Started!" << std::endl;
	_time = time(0);

	m_database = new SqliteDataBase();

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

	///if the user enter exit </summary>
	std::thread commands(&WSServer::getCommands, this);

	//accept clients
	while (true)
	{
		tcp::socket socket{ ioc };
		acceptor.accept(socket);
		std::thread(&WSServer::clientHandle, this, std::move(socket)).detach();
	}
}

void WSServer::clientHandle(tcp::socket socket) {
	bool has_logged_in = false;
	// socket will be const - mutable should be used
	websocket::stream<tcp::socket> ws{ std::move(const_cast<tcp::socket&>(socket)) };
	// Accept the websocket handshake
	ws.accept();

	std::cout << "Connection succesfuly made!" << std::endl;

	this->m_clients.insert(std::pair<websocket::stream<tcp::socket>*, LoginRequestHandler*>(&ws, (LoginRequestHandler*)new LoginRequestHandler()));
	
	beast::flat_buffer buffer;
	ws.write(net::buffer(JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("Error: you are a noob"))));

	while (true)
	{
		try
		{
			beast::flat_buffer buffer;

			// Read a message
			ws.read(buffer);
			auto out = beast::buffers_to_string(buffer.cdata());

			// get the message code
			std::string str2 = out.substr(0, 3);
			int msgCode = atoi(str2.c_str());

			//insert field to RequestInfo struct
			struct RequestInfo request;
			request.msgCode = msgCode;
			request.msgTime = ctime(&_time);
			request.msg = out.substr(3);

			//first, the client need to connect to his user
			LoginRequestHandler* login_Request_Handler = m_clients[&ws];
			if ((!has_logged_in))
			{
				if (!(login_Request_Handler->isRequestRelevant(request)))
				{
					ws.write(net::buffer(JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("You must first log in or sign up"))));
					continue;
				}
				string result = login_Request_Handler->handleRequest(request);
				ws.write(net::buffer(result));
				nlohmann::json j = nlohmann::json::parse(result);
				if (request.msgCode == MT_CLIENT_LOG_IN && j["status"] == LoginCode::loginSuccess)
				{
					has_logged_in = true;
				}
				continue;
			}
			//std::cout << out << std::endl;
			//sent data
			//ws.write(buffer.data());
		}
		catch (beast::system_error const& e)
		{
			if (e.code() != websocket::error::closed)
			{
				std::cout << "Exception was catch in function clientHandler , what=" << e.what() << std::endl;
				break;
			}
		}
		//ws.close();
	}
}

void WSServer::build_receive_message(const RequestInfo request, websocket::stream<tcp::socket> ws)
{
	
} 

void WSServer::getCommands()
{
	std::string command = "";
	while (command != "EXIT") {
		std::cin >> command;
		_exit(1);
	}
}
