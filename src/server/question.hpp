#ifndef _SERVER_QUESTION_HPP
#define _SERVER_QUESTION_HPP

#include <iostream>
#include <string>

class Question
{
	std::string _description;
	std::string _answer;
  public:
	std::string description();
	std::string answer();

	void set_description(std::string);
	void set_answer(std::string);

	Question(std::string, std::string);
	Question();
};

#endif /* _SERVER_QUESTION_HPP */
