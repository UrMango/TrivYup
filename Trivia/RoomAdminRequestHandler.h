#pragma once
#include "IRequestHandler.h"

class RoomAdminRequestHandler : public IRequestHandler
{
private:


public:
	virtual bool isRequestRelevant(const RequestInfo& request) const override;
	virtual RequestResult handleRequest(const RequestInfo& request) override;
};