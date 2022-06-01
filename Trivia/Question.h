#pragma once

#include <iostream>
#include <string>

class Question
{
public:
	Question(int id, std::string question, std::string answer, std::string wrongAnswer, std::string wrongAnswer2, std::string wrongAnswer3);
	~Question() {};

private:
	int id;
	std::string question;
	std::string answer;
	std::string wrongAnswer;
	std::string wrongAnswer2;
	std::string wrongAnswer3;
};
