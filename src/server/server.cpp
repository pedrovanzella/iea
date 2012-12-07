#include "server.hpp"
#include "team.hpp"
#include "session.hpp"
#include <vector>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>


server::server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint) : io_service_(io_service), acceptor_(io_service, endpoint)
{
	teams_.push_back(Team(0)); // First team is team with id 0
	start_accept();
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
	std::vector<Team>::iterator i;
	for (i = teams_.begin(); i != teams_.end(); i++) {
		if (i->id() == id) {
			return *i;
		}
	}

	static Team t(id);
	teams_.push_back(t);
	return t;
}
