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

std::string Question::getQuestion()
{
	return this->m_question;
}

std::string Question::getPossibleAnswers()
{
	std::string answers = "";
	for (int i = 0; i < m_possibleAnswers.size(); i++)
		answers += m_possibleAnswers[i] + ", ";
	return answers;
}