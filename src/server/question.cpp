#include "question.hpp"
#include <iostream>
#include <string>

std::string Question::description()
{
	return _description;
}

std::string Question::answer()
{
	return _answer;
}

void Question::set_description(std::string d)
{
	/* Might want to check this? */
	_description = d;
}

void Question::set_answer(std::string a)
{
	_answer = a;
}

Question::Question(std::string d, std::string a)
{
	/* Calling setters to use their (possible) verifications */
	set_description(d);
	set_answer(a);
}

Question::Question()
{
	_description = "";
	_answer = "";
}
