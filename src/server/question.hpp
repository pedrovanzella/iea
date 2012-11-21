#ifndef _SERVER_QUESTION_HPP
#define _SERVER_QUESTION_HPP

#include <iostream>
#include <string>

class Question
{
	std::string _description;
	std::string _answer;

	/* Private setters, only need to call them on initialize */
	void set_description(std::string);
	void set_answer(std::string);

	friend std::ostream& operator<<(std::ostream&, const Question&);

	static const std::string separator;
  public:
	std::string description() const;
	std::string answer() const;

	explicit Question(std::string, std::string); /* Build with two strings */
	explicit Question(std::string); /* Build with only one, formatted, string */
	Question();
};

#endif /* _SERVER_QUESTION_HPP */
