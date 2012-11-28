#include "question.hpp"
#include <iostream>
#include <string>

using std::string;
using std::ostream;
using std::endl;

const string Question::separator = "#!#";

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

Question::Question(string q)
{
	string::size_type s = q.find_first_of(this->separator);

	string desc(q, 0, s);
	string ans(q.begin() + s + this->separator.size(), q.end());

	_description = desc;
	_answer = ans;
}

Question::Question()
{
	_description = "";
	_answer = "";
}

ostream& operator<<(ostream& os, const Question& q)
{
	os << q.description() << q.separator << q.answer() << endl;
	return os;
}
