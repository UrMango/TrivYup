#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(){}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	RequestHandlerFactory* rr = (RequestHandlerFactory*)this;
	return (LoginRequestHandler*)new LoginRequestHandler(*rr);
}
