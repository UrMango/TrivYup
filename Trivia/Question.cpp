#include "Question.h"

Question::Question(int id, std::string question, std::string answer, std::string wrongAnswer, std::string wrongAnswer2, std::string wrongAnswer3)
{
	this->id = id;
	this->m_question = question;
	m_possibleAnswers.push_back(answer);
	m_possibleAnswers.push_back(wrongAnswer);
	m_possibleAnswers.push_back(wrongAnswer2);
	m_possibleAnswers.push_back(wrongAnswer3);
}
