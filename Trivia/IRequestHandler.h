#pragma once

#include <string>
using std::string;

#include "Helper.h"
class Helper;
enum MessageType;
struct RequestInfo;
struct RequestResult;

enum ReqTypes {
	GAME_REQ = 0,
	LOGIN_REQ,
	MENU_REQ,
	ROOM_ADMIN_REQ,
	ROOM_MEMBER_REQ
};

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo& request) const = 0;
	virtual RequestResult handleRequest(const RequestInfo& request) = 0;
	virtual unsigned short getType() const = 0;
	/*virtual LoggedUser getUser() const = 0;*/
private:
};
