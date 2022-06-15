#pragma once

#include <iostream>
#include <string>
#include <vector>

class Question
{
public:
	Question(int id, std::string question, std::string answer, std::string wrongAnswer, std::string wrongAnswer2, std::string wrongAnswer3);
	~Question() {};
	std::string getQuestion();
	std::string getPossibleAnswers();


private:
	int id;
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
};

