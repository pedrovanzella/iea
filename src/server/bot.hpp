#ifndef _SERVER_BOT_HPP_
#define _SERVER_BOT_HPP_
#include <vector>
#include <string>
#include "question.hpp"
#include "team.hpp"
#include <thread>
// Server tem um Bot
// Bot.run() cria uma thread para cada team
// em cada thread de team, ele cria uma thread de player (?)
// Ele envia, pela thread de team, a mensagem com a pergunta
// para cada cliente, ele ouve a resposta
// compara, pontua, gg evr1

class server;

class Bot
{
	public:
		Bot();
		Bot(server* s) : server_(s) {}

		void run();

		void load_questions();

	private:
		std::vector<Question> questions_;
		server* server_;
		std::vector<std::thread> team_threads_;
};

#endif /* _SERVER_BOT_HPP_ */
