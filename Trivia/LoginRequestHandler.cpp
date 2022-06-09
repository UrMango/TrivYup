#include "LoginRequestHandler.h"


LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory, LoginManager& loginManager) : m_handlerRequest(handlerFactory), m_loginManager(loginManager)
{
	
}

LoginRequestHandler::~LoginRequestHandler(){}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == MT_CLIENT_LOG_IN || request.msgCode == MT_CLIENT_SIGN_UP);
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& request) 
{
	std::string msg;

	if (!(this->isRequestRelevant(request)))
	{
		//insert field to RequestInfo struct
		struct RequestResult result;
		result.msg = JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("You must first log in or sign up"));
		result.newHandler = nullptr; 
	}
	if (request.msgCode == MT_CLIENT_LOG_IN)
	{
		return login(request);
	}
	else if (request.msgCode == MT_CLIENT_SIGN_UP)
	{
		return signUp(request);
	}
}

RequestResult LoginRequestHandler::signUp(const RequestInfo request)const
{
	struct RequestResult result;
	//do deserialize for sign up request
	SignupRequest newUser = JsonRequestPacketDeserializer::deserializeSignupRequest(request.msg); 

	if (m_loginManager.signup(newUser.username, newUser.passward, newUser.email))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse(SignupCode::signupSuccess));
		LoggedUser* loggedUser = new LoggedUser(newUser.username);
		result.newHandler = m_handlerRequest.createMenuRequestHandler(*loggedUser); //change to menu handle
	}
	else
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse(SignupCode::signupError));
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult LoginRequestHandler::login(const RequestInfo request)const
{
	struct RequestResult result;
	//do deserialize for login request
	LoginRequest user = JsonRequestPacketDeserializer::deserializeLoginRequest(request.msg); 

	if (m_loginManager.login(user.username, user.passward))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse(LoginCode::loginSuccess));
		LoggedUser* loggedUser = new LoggedUser(user.username);
		result.newHandler = m_handlerRequest.createMenuRequestHandler(*loggedUser); //change to menu handle
	}
	else
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse(LoginCode::loginError));
		result.newHandler = nullptr;

	}
	return result;
}