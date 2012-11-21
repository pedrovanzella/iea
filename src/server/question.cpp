#include "question.hpp"
#include <iostream>
#include <string>

using std::string;
using std::ostream;
using std::endl;

string Question::description() const
{
	return _description;
}

string Question::answer() const
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

ostream& operator<<(ostream& os, const Question& q)
{
	os << q.description() << "#!#" << q.answer() << endl;
	return os;
}
