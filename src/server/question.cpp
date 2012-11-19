#include "question.hpp"
#include <iostream>
#include <string>

using std::string;

string Question::description()
{
	return _description;
}

string Question::answer()
{
	return _answer;
}

void Question::set_description(string d)
{
	/* Might want to check this? */
	_description = d;
}

void Question::set_answer(string a)
{
	_answer = a;
}

Question::Question(string d, string a)
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
