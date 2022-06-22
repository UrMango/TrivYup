#include "Communicator.h"


Communicator::Communicator(RequestHandlerFactory& handlerFactory, IDatabase& database) : m_handlerFactory(handlerFactory), m_database(database)
{
	_time = time(0);
	this->startHandleRequests();
}

Communicator::~Communicator() {}

void Communicator::startHandleRequests()
{
	auto const address = net::ip::make_address("127.0.0.1");
	auto const port = static_cast<unsigned short>(std::atoi("8083"));

	try {
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
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}
}


void Communicator::handleNewClient(tcp::socket socket) {

	// socket will be const - mutable should be used
	websocket::stream<tcp::socket> ws{ std::move(const_cast<tcp::socket&>(socket)) };
	// Accept the websocket handshake
	try {
		ws.accept();
	}
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}

	std::cout << "Connection succesfuly made!" << std::endl;

	_clientsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
		this->m_clients.insert(std::pair<websocket::stream<tcp::socket>*, IRequestHandler*>(&ws, (LoginRequestHandler*)m_handlerFactory.createLoginRequestHandler()));
	_clientsMtx.unlock();//if mtx locked: this thread unlocks it! if mtx unlocked: this thread waits until it is locked

	beast::flat_buffer buffer;

	//msg to client
	try {
		ws.write(net::buffer(JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("Error: you are a noob"))));
	}
	catch (...) {
		std::cout << "Catch an error" << '\n';
	}
	ctime(&_time);
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
			_time = time(0);
			ctime(&_time);
			request.msgTime = _time;
			request.msg = out.substr(3);

			//first, the client need to connect to his user
			RequestResult res = m_clients[&ws]->handleRequest(request);

			//change handel
			if (res.newHandler != nullptr)
			{
				if (request.msgCode != START_GAME && request.msgCode != CLOSE_ROOM && request.msgCode != CLOSE_GAME) {
					_clientsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
						delete(m_clients[&ws]);
						m_clients[&ws] = res.newHandler;
					_clientsMtx.unlock();//if mtx locked: this thread unlocks it! if mtx unlocked: this thread waits until it is locked
				}
			}

			//requests that send to every client that in a specific room or game
			if (ws.is_open() && (request.msgCode == START_GAME || request.msgCode == CLOSE_ROOM))
			{
				if (m_clients[&ws]->getType() == ReqTypes::ROOM_ADMIN_REQ)//if the handel is room admin
				{
					RoomAdminRequestHandler* userRequestHandler = (RoomAdminRequestHandler*)(m_clients[&ws]);
					RoomMemberRequestHandler* otherUserRequestHandler;

					ws.write(net::buffer(res.msg));  //admin

					for (int x = 1; x < userRequestHandler->getRoomOfUser()->getAllUsers().size(); x++)
					{
						_clientsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
						for (auto i : m_clients)
						{
							if (i.second->getType() != ReqTypes::ROOM_MEMBER_REQ) continue; //check if the handel if room member
							otherUserRequestHandler = (RoomMemberRequestHandler*)i.second; //get the handel of room member

							//check if it's the client
							if (otherUserRequestHandler->getUser().getUsername() == (userRequestHandler->getRoomOfUser()->getAllUsers())[x] && (request.msgCode == START_GAME || request.msgCode == CLOSE_ROOM))
							{
								(*(i.first)).write(net::buffer(res.msg));

								if (request.msgCode == START_GAME)
								{
									//sends to the clients in the room to start the game
									auto handler = this->m_handlerFactory.createGameRequestHandler(otherUserRequestHandler->getUser(), *this->m_handlerFactory.getGameManager().getGame(userRequestHandler->getRoomOfUser()->getRoomData().id), this->m_handlerFactory.getGameManager());
									delete(i.second);
									m_clients[i.first] = handler;
								}
								else if (request.msgCode == CLOSE_ROOM)
								{
									//sends to the clients in the room to close the room because the admin closed it
									auto handler = this->m_handlerFactory.createMenuRequestHandler(otherUserRequestHandler->getUser());
									delete(i.second);
									m_clients[i.first] = handler;
								}
							}
						}
						_clientsMtx.unlock();//if mtx locked: this thread unlocks it! if mtx unlocked: this thread waits until it is locked

					}
					_clientsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
					delete(m_clients[&ws]);
					m_clients[&ws] = res.newHandler;
					_clientsMtx.unlock();//if mtx locked: this thread unlocks it! if mtx unlocked: this thread waits until it is locked
				}
			}
			else if (request.msgCode == SUBMIT_ANSWER && ws.is_open()) //After each player answers, check if all the players have already answered - it can move on to the next question if everyone has already answered and the timer is not over
			{
				ws.write(net::buffer(res.msg));

				if (m_clients[&ws]->getType() == ReqTypes::GAME_REQ) {//cheks if the handel is game

					GameRequestHandler* userRequestHandler = (GameRequestHandler*)(m_clients[&ws]);
					GameRequestHandler* otherUserRequestHandler;
					int gameId = userRequestHandler->getGame().getGameId();

					if (this->m_handlerFactory.getGameManager().getGame(gameId)->getIsEveryoneAnswerd())
					{
						//get players in game
						for (auto x : userRequestHandler->getGame().getPlayers())
						{
							_clientsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
								for (auto i : m_clients)
								{
									if (i.second->getType() != ReqTypes::GAME_REQ) continue; //cheks if the player in game handel
									otherUserRequestHandler = (GameRequestHandler*)(i.second);

									//sends a msg that says everyone has already answered
									if (otherUserRequestHandler->getUser().getUsername() == x.first->getUsername())
									{
										GetIsEveryoneAnsweredResponse getIsEveryoneAnsweredResponse;
										getIsEveryoneAnsweredResponse.isEveryoneAnswered = true;
										(*(i.first)).write(net::buffer(JsonResponsePacketSerializer::serializeIsEveryoneAnsweredResponse(getIsEveryoneAnsweredResponse)));
									}
								}
							_clientsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked

						}
					}
				}	

			}
			else if (request.msgCode == CLOSE_GAME) {
				ws.write(net::buffer(res.msg));

				if (m_clients[&ws]->getType() == ReqTypes::GAME_REQ)//
				{
					GameRequestHandler* userRequestHandler = (GameRequestHandler*)(m_clients[&ws]);
					GameRequestHandler* otherUserRequestHandler;

					for (auto x : userRequestHandler->getGame().getPlayers())
					{
						_clientsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
							for (auto i : m_clients)
							{	
								
								if (!i.first) continue;

								//cheks if the player in game handel
								if (i.second->getType() != ReqTypes::GAME_REQ) continue;
								otherUserRequestHandler = (GameRequestHandler*)(i.second);

								if (x.first->getUsername() == otherUserRequestHandler->getUser().getUsername()) {
									//sends a msg that the room has closed
									if (i.first->is_open()) { 
										(*(i.first)).write(net::buffer(res.msg));
									}

									//go back to menu handler
									auto handler = this->m_handlerFactory.createMenuRequestHandler(otherUserRequestHandler->getUser());
									delete(i.second);
									m_clients[i.first] = handler;
								}

							}
						_clientsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
					}
					_clientsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
						delete(m_clients[&ws]);
						m_clients[&ws] = res.newHandler;
					_clientsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
				}
			}
			else if (ws.is_open())
				ws.write(net::buffer(res.msg));

		}
		catch (beast::system_error const& e)
		{
			if (e.code() != websocket::error::closed)
			{
				std::cout << "Exception was catch in function clientHandler , what=" << e.what() << std::endl;
				if (!ws.is_open()) {
					if (m_clients[&ws]->getType() == ReqTypes::GAME_REQ) {
						_clientsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
							GameRequestHandler* handler = (GameRequestHandler*)(m_clients[&ws]);
							handler->getGame().removePlayer(&handler->getUser());
							delete(m_clients[&ws]);
						_clientsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
					}
					else if (m_clients[&ws]->getType() == ReqTypes::ROOM_MEMBER_REQ) {
						_clientsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
							RoomMemberRequestHandler* handler = (RoomMemberRequestHandler*)(m_clients[&ws]);
							handler->leaveRoom(RequestInfo());
							delete(m_clients[&ws]);
						_clientsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
					}
					else if (m_clients[&ws]->getType() == ReqTypes::ROOM_ADMIN_REQ) {
						_clientsMtx.lock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
							RoomAdminRequestHandler* handler = (RoomAdminRequestHandler*)(m_clients[&ws]);
							handler->closeRoom(RequestInfo());
							delete(m_clients[&ws]);
						_clientsMtx.unlock();//if mtx unlocked: this thread locks it! if mtx locked: this thread waits until unlocked
					}
				}
				break;
			}
		}
		catch (...) {
			std::cout << "Default Exception\n";
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

