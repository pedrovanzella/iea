#include "server.hpp"
#include "team.hpp"
#include "session.hpp"
#include "bot.hpp"
#include <vector>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>


server::server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint) : io_service_(io_service), acceptor_(io_service, endpoint), gamemaster(this)
{
	for (int i = 0; i <= 9; i++) {
		teams_.push_back(Team(i)); // First team is team with id 0
	}
	start_accept();
	gamemaster.run();
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
	static Team t = NULL;
	return t; // Gambiarra
}
