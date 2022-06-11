#include "WSServer.h"
WSServer::WSServer()
{
	std::cout << "Server Started!" << std::endl;
	m_database = new SqliteDataBase();
	m_handlerFactory = new RequestHandlerFactory(m_database);
	m_communicator = new Communicator(*m_handlerFactory, *m_database);
	this->run();
}

void WSServer::run()
{
	m_communicator->startHandleRequests();
}

WSServer::~WSServer() {}
