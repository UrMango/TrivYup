#pragma once

#include <vector>
#include <string>
#include <WinSock2.h>
#include <boost/beast.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>

using tcp = boost::asio::ip::tcp;
using std::string;

enum MessageType 
{
	MT_CLIENT_LOG_IN = 200,
	MT_CLIENT_SIGN_UP = 204,

	MT_CLIENT_FINISH = 207,
	MT_CLIENT_EXIT = 208,
	MT_SERVER_UPDATE = 101,
};
struct RequestInfo {
	int msgCode = 0;
	string msgTime = "";
	string msg = "";
};

class Helper
{
public:


	//static int getMessageTypeCode(const tcp::socket sc);
	//static int getIntPartFromSocket(const tcp::socket sc, const int bytesNum);
	//static std::string getStringPartFromSocket(tcp::socket sc, const int bytesNum);
	//static void sendData(const tcp::socket sc, const std::string message);

private:
	//static std::string getPartFromSocket(const tcp::socket sc, const int bytesNum);
	//static std::string getPartFromSocket(const tcp::socket sc, const int bytesNum, const int flags);

};
