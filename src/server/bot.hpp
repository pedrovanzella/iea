#ifndef _SERVER_BOT_HPP_
#define _SERVER_BOT_HPP_
#include "question.hpp"
#include "vector"

class Bot
{
	public:
		Bot() {}

		void load_questions();

		const Question& rand_question() const;
		void ask();
		void check_answer();

	private:
		vector<Question> questions_;
		Question last_question_asked;
};

#endif /* _SERVER_BOT_HPP_ */
