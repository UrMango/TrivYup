#include "Question.h"

Question::Question(int id, std::string question, std::string answer, std::string wrongAnswer, std::string wrongAnswer2, std::string wrongAnswer3)
{
	this->id = id;
	this->question = question;
	this->answer = answer;
	this->wrongAnswer = wrongAnswer;
	this->wrongAnswer2 = wrongAnswer2;
	this->wrongAnswer3 = wrongAnswer3;
}
