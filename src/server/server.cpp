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

server::server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint) : io_service_(io_service), acceptor_(io_service, endpoint)
{
	for (int i = 0; i <= 9; i++) {
	    teams_.push_back(Team(i)); // First team is team with id 0
		std::cout << "Criei time " << teams_[i].id() << std::endl;
	}
	start_accept();
	run();
}

void server::start_accept()
{
	session_ptr new_session(new session(io_service_, teams_[0], this));
	acceptor_.async_accept(new_session->socket(),
			boost::bind(&server::handle_accept, this, new_session,
				boost::asio::placeholders::error));
}

void server::handle_accept(session_ptr session, const boost::system::error_code& error)
{
	if (!error) {
		session->start();
		sessions_.push_back(session);
	}
	
	start_accept();
}

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

void server::run()
{
	std::cout << "Loading questions" << std::endl;
	load_questions();
	std::cout << "Questions loaded" << std::endl;

	std::vector<Team>::size_type i;
	for (i = 0; i != teams_.size(); i++) {
	    // Cria uma thread por team, passa uma referência pro team pra thread
	    std::cout << "Achei time " << teams_[i].id() << std::endl;
		team_threads[i] = boost::thread(boost::thread(&server::run_game, teams_[i]));

		team_threads[i].join();
	}
}

static boost::mutex team_print_mutex;
void server::run_game(Team& t)
{
	team_print_mutex.lock();
	std::cout << "[" << t.id() << "]" << std::endl;
	team_print_mutex.unlock();
}
