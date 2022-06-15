#pragma once

#include <iostream>
#include <string>
#include <vector>

class Question
{
public:
	Question(const int id, const std::string question, const std::string answer, const std::string wrongAnswer, const std::string wrongAnswer2, const std::string wrongAnswer3);
	~Question() {};
	std::string getQuestion() const;
	std::string getPossibleAnswers() const;
	std::string getCorrentAnswer() const;


private:
	int id;
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
};

