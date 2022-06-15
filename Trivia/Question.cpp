#include "Question.h"

Question::Question(const int id, const std::string question, const std::string answer, const std::string wrongAnswer, const std::string wrongAnswer2, const std::string wrongAnswer3)
{
	this->id = id;
	this->m_question = question;
	m_possibleAnswers.push_back(answer);
	m_possibleAnswers.push_back(wrongAnswer);
	m_possibleAnswers.push_back(wrongAnswer2);
	m_possibleAnswers.push_back(wrongAnswer3);
}

std::string Question::getQuestion() const
{
	return this->m_question;
}

std::string Question::getPossibleAnswers() const
{
	std::string answers = "";
	for (int i = 0; i < m_possibleAnswers.size(); i++)
		answers += m_possibleAnswers[i] + ", ";
	return answers;
}

std::string Question::getCorrentAnswer() const
{
	return m_possibleAnswers[0];
}