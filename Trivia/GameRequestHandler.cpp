#include "GameRequestHandler.h"

void randomShuffleOfMap(std::map<unsigned int, std::string>& Question);

Game& GameRequestHandler::getGame()
	{
	return this->m_game;
}

LoggedUser& GameRequestHandler::getUser() const
{
	return this->m_user;
}

unsigned short GameRequestHandler::getType() const
{
	return ReqTypes::GAME_REQ;
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& request) const
{
	return (request.msgCode == LEAVE_GAME || request.msgCode == GET_QUESTION || request.msgCode == SUBMIT_ANSWER || request.msgCode == GET_GAME_RESULT || request.msgCode == CLOSE_GAME);
}

//***********************************************************************************************
//the func return a answer for request
//***********************************************************************************************
RequestResult GameRequestHandler::handleRequest(const RequestInfo& request)
{
	struct RequestResult result;

	if (!(this->isRequestRelevant(request)))
	{
		//insert field to RequestInfo struct
		result.msg = JsonResponsePacketSerializer::serializeErrorResponse(ErrorResponse("GameRequestHandler - Its not a valid request"));
		result.newHandler = nullptr;
		return result;
	}
	switch (request.msgCode) {
		case LEAVE_GAME:
			leaveRoom(request);
			break;
		case GET_QUESTION:
			return getQuestion(request);
			break;
		case SUBMIT_ANSWER:
			return sumbitAns(request);
			break;
		case GET_GAME_RESULT:
			return getRoomRes(request);
			break;
		case CLOSE_GAME:
			return closeGame(request);
			break;
	}
	return result;
}

RequestResult GameRequestHandler::sumbitAns(const RequestInfo& request)const
{
	SubmitAnswerRequest submitAnswerRequest;
	SubmitAnswerResponse submitAnswerResponse;
	struct RequestResult result;

	if (this->m_game.getPlayerData(&this->m_user)->hasAnswered)
	{
		ErrorResponse errorResponse("You can't answer more than once...");
		result.msg = JsonResponsePacketSerializer::serializeErrorResponse(errorResponse);
		result.newHandler = nullptr;
		return result;
	}
	submitAnswerRequest = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(request.msg);
	submitAnswerResponse.correctAnswer = this->m_game.submitAnswer(&this->m_user, submitAnswerRequest.answer);

	if (submitAnswerRequest.answer == submitAnswerResponse.correctAnswer)
		submitAnswerResponse.status = 1;
	else
		submitAnswerResponse.status = 0;

	submitAnswerResponse.everyoneAnswerd = this->m_game.getIsEveryoneAnswerd();
	result.msg = JsonResponsePacketSerializer::serializeSubmitAnswerResponse(submitAnswerResponse);
	result.newHandler = nullptr;
	return result;
}

RequestResult GameRequestHandler::getQuestion(const RequestInfo& request)const
{
	GetQuestionResponse getQuestionResponse;
	struct RequestResult result;

	Question* qu = this->m_game.getQuestionForUser(&this->m_user, request.msgTime);
	if (qu == nullptr)
	{
		getQuestionResponse.status = 0;
		getQuestionResponse.question = "";
		getQuestionResponse.answers = {};
	}
	else
	{
		getQuestionResponse.status = 1;
		std::map<unsigned int, std::string> Question = qu->getPossibleAnswers();
		randomShuffleOfMap(Question);

		getQuestionResponse.question = qu->getQuestion();
		getQuestionResponse.answers = Question;
	}
	result.msg = JsonResponsePacketSerializer::serializeGetQuestionResponse(getQuestionResponse);
	result.newHandler = nullptr;
	return result;
}

RequestResult GameRequestHandler::closeGame(const RequestInfo& request)
{
	CloseGameResponse closeGameResponse;
	struct RequestResult result;
	this->m_handlerFacroty.getGameManager().deleteGame(this->getGame().getGameId());
	this->m_handlerFacroty.getRoomManager().deleteRoom(this->getGame().getGameId());
	closeGameResponse.status = 1;
	result.msg = JsonResponsePacketSerializer::serializeCloseGameResponse(closeGameResponse);
	result.newHandler = this->m_handlerFacroty.createMenuRequestHandler(this->m_user);;
	return result;
}

RequestResult GameRequestHandler::leaveRoom(const RequestInfo& request)const
{
	LeaveGameResponse leaveGameResponse;
	struct RequestResult result;
	leaveGameResponse.status = 1;

	this->m_game.removePlayer(&this->m_user);
	if (m_user.getRoom()) {
		m_user.getRoom()->removeUser(&m_user);
	}
	this->m_user.removeRoom();

	//insert field to RequestInfo struct
	result.msg = JsonResponsePacketSerializer::serializeLeaveGameResponse(leaveGameResponse);
	result.newHandler = this->m_handlerFacroty.createMenuRequestHandler(this->m_user);
	return result;
}

RequestResult GameRequestHandler::getRoomRes(const RequestInfo& request)const
{
	GetGameResultsResponse getGameResultsResponse;
	struct RequestResult result;

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
}

//***********************************************************************************************
//The function mixes a map
//***********************************************************************************************
void randomShuffleOfMap(std::map<unsigned int, std::string> &Question)
{
	std::vector<std::string> v;
	int counter = 0;
	for (auto it = Question.begin(); it != Question.end(); ++it)
	{
		v.push_back(it->second);
	}
	std::random_shuffle(v.begin(), v.end());
	for (auto it = Question.begin(); it != Question.end(); ++it)
	{
		it->second = v[counter];
		counter++;
	}
}