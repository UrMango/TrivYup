#include "Communicator.h"
Communicator::Communicator(RequestHandlerFactory& handlerFactory, IDatabase& database) : m_handlerFactory(handlerFactory), m_database(database)
{
	_time = time(0);
	this->startHandleRequests();
}

Communicator::~Communicator(){}

void Communicator::startHandleRequests()
{
	auto const address = net::ip::make_address("127.0.0.1");
	auto const port = static_cast<unsigned short>(std::atoi("8079"));

	net::io_context ioc{ 1 };
	tcp::acceptor acceptor{ ioc, {address, port} };

	///if the user enter exit </summary>
	std::thread commands(&Communicator::getCommands, this);

	//accept clients
	while (true)
	{
		tcp::socket socket{ ioc };
		acceptor.accept(socket);
		std::thread(&Communicator::handleNewClient, this, std::move(socket)).detach();
	}
}

void Communicator::handleNewClient(tcp::socket socket) {
	// socket will be const - mutable should be used
	websocket::stream<tcp::socket> ws{ std::move(const_cast<tcp::socket&>(socket)) };
	// Accept the websocket handshake
	ws.accept();

	std::cout << "Connection succesfuly made!" << std::endl;

	this->m_clients.insert(std::pair<websocket::stream<tcp::socket>*, IRequestHandler*>(&ws, (LoginRequestHandler*)m_handlerFactory.createLoginRequestHandler()));

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
			ctime(&_time);
			request.msgTime = _time;
			request.msg = out.substr(3);

			//first, the client need to connect to his user
			RequestResult res = m_clients[&ws]->handleRequest(request);
			
			if (res.newHandler != nullptr)
			{
				if (request.msgCode != START_GAME) {
					delete(m_clients[&ws]);
					m_clients[&ws] = res.newHandler;
				}
			}
			
			if (ws.is_open() && (request.msgCode == START_GAME || request.msgCode == CLOSE_ROOM))
			{
				RoomAdminRequestHandler* userRequestHandler = (RoomAdminRequestHandler*)(m_clients[&ws]);
				RoomMemberRequestHandler* otherUserRequestHandler;
				for (int x = 0; x < userRequestHandler->getRoomOfUser()->getAllUsers().size(); x++)
				{
					if (x == 0) //admin
					{
						ws.write(net::buffer(res.msg));
					}
					else
					{
						bool sendToServer = false;
						for (auto i : m_clients)
						{							
							if (i.second->getUser().getUsername() == (userRequestHandler->getRoomOfUser()->getAllUsers())[x])
							{								
								otherUserRequestHandler = (RoomMemberRequestHandler*)(i.second);
								if (request.msgCode == START_GAME)
								{
									i.second = this->m_handlerFactory.createGameRequestHandler(otherUserRequestHandler->getUser(), *this->m_handlerFactory.getGameManager().getGame(userRequestHandler->getRoomOfUser()->getRoomData().id), this->m_handlerFactory.getGameManager());
									(*(i.first)).write(net::buffer(res.msg));
								}
								else if (request.msgCode == CLOSE_ROOM)
								{
									(*(i.first)).write(net::buffer(res.msg));
									i.second = this->m_handlerFactory.createMenuRequestHandler(otherUserRequestHandler->getUser());
								}
							}

						}
						m_clients[&ws] = res.newHandler;
					}
				}
			}
			else if (request.msgCode == SUBMIT_ANSWER && ws.is_open())
			{
				ws.write(net::buffer(res.msg));
				GameRequestHandler* userRequestHandler = (GameRequestHandler*)(m_clients[&ws]);
				GameRequestHandler* otherUserRequestHandler;
				int gameId = userRequestHandler->getGame().getGameId();
				if (this->m_handlerFactory.getGameManager().getGame(gameId)->getIsEveryoneAnswerd())
				{
					
					for (auto x : userRequestHandler->getGame().getPlayers())
					{
						for (auto i : m_clients)
						{
							otherUserRequestHandler = (GameRequestHandler*)(i.second);
							if (otherUserRequestHandler->getUser().getUsername() == x.first->getUsername())
							{
								GetIsEveryoneAnsweredResponse getIsEveryoneAnsweredResponse;
								getIsEveryoneAnsweredResponse.isEveryoneAnswered = true;
								(*(i.first)).write(net::buffer(JsonResponsePacketSerializer::serializeIsEveryoneAnsweredResponse(getIsEveryoneAnsweredResponse)));

								i.second = this->m_handlerFactory.createMenuRequestHandler(otherUserRequestHandler->getUser());
								this->m_handlerFactory.getGameManager().deleteGame(gameId);
								this->m_handlerFactory.getRoomManager().deleteRoom(gameId);
							}
						}
					}
				}

				if (this->m_handlerFactory.getGameManager().getGame(gameId)->getIsFinished())
				{
					GameRequestHandler* userRequestHandler = (GameRequestHandler*)(m_clients[&ws]);
					GameRequestHandler* otherUserRequestHandler;
					for (auto x : userRequestHandler->getGame().getPlayers())
					{
						for (auto i : m_clients)
						{
							otherUserRequestHandler = (GameRequestHandler*)(i.second);
							if (otherUserRequestHandler->getUser().getUsername() == x.first->getUsername())
							{
								i.second = this->m_handlerFactory.createMenuRequestHandler(otherUserRequestHandler->getUser());
								
							}
						}
					}
					this->m_handlerFactory.getGameManager().deleteGame(gameId);
					this->m_handlerFactory.getRoomManager().deleteRoom(gameId);
				}

			}	
			else if(ws.is_open())
				ws.write(net::buffer(res.msg));
			
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

void Communicator::getCommands()
{
	std::string command = "";
	while (command != "EXIT") {
		std::cin >> command;
		_exit(1);
	}
}
