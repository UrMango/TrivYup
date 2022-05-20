#include "Helper.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

using std::string;

/*
// recieves the type code of the message from socket (3 bytes)
// and returns the code. if no message found in the socket returns 0 (which means the client disconnected)
int Helper::getMessageTypeCode(const tcp::socket sc)
{
	std::string msg = getPartFromSocket(sc, 3, 0);

	if (msg == "")
		return 0;

	int res = std::atoi(msg.c_str());
	return res;
}


// recieve data from socket according byteSize
// returns the data as int
int Helper::getIntPartFromSocket(const tcp::socket sc, const int bytesNum)
{
	return atoi(getPartFromSocket(sc, bytesNum, 0).c_str());
}

// recieve data from socket according byteSize
// returns the data as string
string Helper::getStringPartFromSocket(const tcp::socket sc, const int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}


// recieve data from socket according byteSize
// this is private function
std::string Helper::getPartFromSocket(const tcp::socket sc, const int bytesNum)
{
	return getPartFromSocket(sc, bytesNum, 0);
}

// send data to socket
// this is private function
void Helper::sendData(const tcp::socket sc, const std::string message)
{
	const char* data = message.c_str();

	if (send(sc, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

std::string Helper::getPartFromSocket(const tcp::socket sc, const int bytesNum, const int flags)
{
	if (bytesNum == 0)
	{
		return "";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum, flags);
	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	data[bytesNum] = 0;
	std::string received(data);
	delete[] data;
	return received;
}*/