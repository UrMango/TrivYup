#include "LoginRequestHandler.h"


LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerRequest(handlerFactory), m_loginManager(*(new LoginManager(new SqliteDataBase()))) {}

LoginRequestHandler::~LoginRequestHandler(){}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == MT_CLIENT_LOG_IN || request.msgCode == MT_CLIENT_SIGN_UP);
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& request) const
{
	std::string msg;
	struct RequestResult result;

	if (!(this->isRequestRelevant(request)))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("You must first log in or sign up"));
		result.newHandler = nullptr; 

	}
	if (request.msgCode == MT_CLIENT_LOG_IN)
	{
		return login(request);
	}
	else if (request.msgCode == MT_CLIENT_SIGN_UP)
	{
		SignupRequest newUser = JsonRequestPacketDeserializer::deserializeSignupRequest(request.msg); //SignupRequest
		
		if (m_loginManager.signup(newUser.username, newUser.passward, newUser.email))
		{
			result.msg = JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse(SignupCode::signupSuccess));
			result.newHandler = (IRequestHandler*)this; //change to menu handle
		}
		else
		{
			result.msg = JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse(SignupCode::signupError));
			result.newHandler = nullptr; 
		}
	}
	return result;
}

RequestResult LoginRequestHandler::signUp(const RequestInfo request)const
{
	struct RequestResult result;
	SignupRequest newUser = JsonRequestPacketDeserializer::deserializeSignupRequest(request.msg); //SignupRequest

	if (m_loginManager.signup(newUser.username, newUser.passward, newUser.email))
	{
		result.msg = JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse(SignupCode::signupSuccess));
		result.newHandler = (IRequestHandler*)this; //change to menu handle
	}
	else
	{
		result.msg = JsonResponsePacketSerializer::serializeSignupResponse(SignupResponse(SignupCode::signupError));
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult LoginRequestHandler::login(const RequestInfo request)const
{
	struct RequestResult result;
	LoginRequest user = JsonRequestPacketDeserializer::deserializeLoginRequest(request.msg); //LoginRequest
	if (m_loginManager.login(user.username, user.passward))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse(LoginCode::loginSuccess));
		result.newHandler = (IRequestHandler*)this; //change to menu handle
	}
	else
	{
		result.msg = JsonResponsePacketSerializer::serializeLoginResponse(LoginResponse(LoginCode::loginError));
		result.newHandler = nullptr;
	}
	return result;
}