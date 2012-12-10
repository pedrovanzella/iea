#ifndef _SERVER_BOT_HPP_
#define _SERVER_BOT_HPP_
#include <vector>
#include <string>
#include "question.hpp"
// Server tem um Bot
// Bot.run() cria uma thread para cada team
// em cada thread de team, ele cria uma thread de player (?)
// Ele envia, pela thread de team, a mensagem com a pergunta
// para cada cliente, ele ouve a resposta
// compara, pontua, gg evr1

class Bot
{
	public:
		Bot() {}

		void run();

		void load_questions();

		void ask();
		void check_answer(std::string);

	private:
		std::vector<Question> questions_;
		Question last_question_asked;
};

#endif /* _SERVER_BOT_HPP_ */
