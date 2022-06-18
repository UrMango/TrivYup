#pragma once

#include <iostream>
#include <string>
#include <map>
#include <vector>

class Question
{
public:
	Question(const int id, const std::string question, const std::string answer, const std::string wrongAnswer, const std::string wrongAnswer2, const std::string wrongAnswer3);
	~Question() {};
	std::string getQuestion() const;
	std::map<unsigned int, std::string> getPossibleAnswers() const;
	std::string getCorrectAnswer() const;
	int getId() const;

private:
	int id;
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
};

