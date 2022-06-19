#include "GameRequestHandler.h"

Game& GameRequestHandler::getGame()
{
	return this->m_game;
}

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

	SubmitAnswerRequest submitAnswerRequest;
	SubmitAnswerResponse submitAnswerResponse;

	GetGameResultsResponse getGameResultsResponse;

	LeaveGameResponse leaveGameResponse;

	if (!(this->isRequestRelevant(request)))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("GameRequestHandler - Its not a valid request"));
		result.newHandler = nullptr;
		return result;
	}
	switch (request.msgCode) {
		case LEAVE_GAME:
			leaveGameResponse.status = 1;

			this->m_game.removePlayer(&this->m_user);
			if (m_user.getRoom()) {
				m_user.getRoom()->removeUser(m_user);
			}
			this->m_user.removeRoom();
			//insert field to RequestInfo struct
			result.msg = JsonResponsePacketSerializer::serializeLeaveGameResponse(leaveGameResponse);
			result.newHandler = this->m_handlerFacroty.createMenuRequestHandler(this->m_user);
			return result;
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
			submitAnswerRequest = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(request.msg);
			submitAnswerResponse.status = 1;
			submitAnswerResponse.correctAnswer = this->m_game.submitAnswer(&this->m_user, submitAnswerRequest.answer);
			submitAnswerResponse.everyoneAnswerd = this->m_game.getIsEveryoneAnswerd();
			result.msg = JsonResponsePacketSerializer::serializeSubmitAnswerResponse(submitAnswerResponse);
			result.newHandler = nullptr;
			return result;
			break;
		case GET_GAME_RESULT:
			if (this->m_game.getIsFinished() == true)
			{
				getGameResultsResponse.status = 1;
				getGameResultsResponse.results = this->m_game.getAllPlayerResults();

			}
			else
			{
				getGameResultsResponse.status = 0;
				getGameResultsResponse.results = {};
			}
			result.msg = JsonResponsePacketSerializer::serializeGetGameResultsResponse(getGameResultsResponse);
			result.newHandler = nullptr;
			return result;
			break;
	}
	
	return result;
}
