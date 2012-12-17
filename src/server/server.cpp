#include "server.hpp"
#include "team.hpp"
#include "session.hpp"
#include "question.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread.hpp>

/* Inicia o servidor, criando 10 times (somente por questões de performance */
server::server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint) : io_service_(io_service), acceptor_(io_service, endpoint)
{
	for (int i = 0; i <= 9; i++) {
	    teams_.push_back(Team(i)); // First team is team with id 0
		std::cout << "Criei time " << teams_[i].id() << std::endl;
	}
	start_accept();
	run();
}

/* Começa a aceitar conexões */
void server::start_accept()
{
	session_ptr new_session(new session(io_service_, teams_[0], this)); /* Quando chega uma nova conexão, cria uma nova sessão pra ela */
	acceptor_.async_accept(new_session->socket(),
			boost::bind(&server::handle_accept, this, new_session,
				boost::asio::placeholders::error));
}

/* Coloca a sessão no vetor de sessões para sabermos quem está conectado */
void server::handle_accept(session_ptr session, const boost::system::error_code& error)
{
	if (!error) {
		session->start();
		sessions_.push_back(session);
	}
	
	start_accept();
}

/* Retorna uma referência para um time com a ID fornecida. Se ele não existir, cria um novo time */
Team& server::team_with_id(int id)
{
	std::cout << "Will look for team with ID " << id << std::endl;
	std::vector<Team>::iterator i;
	for (i = teams_.begin(); i != teams_.end(); i++) {
		if (i->id() == id) {
			std::cout << "Found Team with ID " << i->id() << std::endl;
			return *i;
		}
	}

	std::cout << "No Team with ID " << id << " found!" << std::endl;
	Team* t = new Team(id);
	teams_.push_back(*t);
	return *t;
}

/* Carrega a db de questões */
void server::load_questions()
{
	std::ifstream infile;
	infile.open("questionsdb", std::ifstream::in);

	std::string newquestion;
	while(std::getline(infile, newquestion)) {
	    Question q(newquestion);
	    questions_.push_back(q);
	}
}

/* Bot que controla o jogo */
void server::run()
{
	std::cout << "Loading questions" << std::endl;
	load_questions();
	std::cout << "Questions loaded" << std::endl;

	std::vector<Team>::iterator i;
	for (i = teams_.begin(); i != teams_.end(); i++) {
	    // Cria uma thread por team, passa uma referência pro team pra thread
	    std::cout << "Achei time " << i->id() << std::endl;
		//boost::thread t(&server::run_game, *i);

		//t.join();
	}
}

static boost::mutex team_print_mutex;
/* Bot individual de cada time */
void server::run_game(Team& t)
{
	team_print_mutex.lock();
	std::cout << "[" << t.id() << "]" << std::endl;
	team_print_mutex.unlock();
}
