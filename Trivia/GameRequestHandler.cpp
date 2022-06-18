#include "GameRequestHandler.h"

bool GameRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == LEAVE_GAME || request.msgCode == GET_QUESTION || request.msgCode == SUBMIT_ANSWER || request.msgCode == GET_GAME_RESULT);
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& request)
{
	std::string msg;
	struct RequestResult result;
	Question* qu;

	GetQuestionResponse getQuestionResponse;


	if (!(this->isRequestRelevant(request)))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("Its not a valid request"));
		result.newHandler = nullptr;
		return result;
	}
	switch (request.msgCode) {
		case LEAVE_GAME:
			break;
		case GET_QUESTION:
			qu = this->m_game.getQuestionForUser(&this->m_user, request.msgTime);
			if (qu == NULL)
			{
				getQuestionResponse.status = 0;
				getQuestionResponse.question = "";
				getQuestionResponse.answers = {};
			}
			else
			{
				getQuestionResponse.status = 1;
				getQuestionResponse.question = qu->getQuestion();
				getQuestionResponse.answers = qu->getPossibleAnswers();
			}
			result.msg = JsonResponsePacketSerializer::serializeGetQuestionResponse(getQuestionResponse);
			result.newHandler = nullptr;
			delete qu;
			return result;
			break;
		case SUBMIT_ANSWER:

			break;
		case GET_GAME_RESULT:
	

			break;
	}
	return result;
}
