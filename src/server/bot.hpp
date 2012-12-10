#ifndef _SERVER_BOT_HPP_
#define _SERVER_BOT_HPP_
#include <vector>
#include <string>
#include "question.hpp"

class Bot
{
	public:
		Bot() {}

		void load_questions();

		Question& ask();
		void check_answer(std::string);

	private:
		const Question& rand_question() const;
		std::vector<Question> questions_;
		Question last_question_asked;
};

#endif /* _SERVER_BOT_HPP_ */
