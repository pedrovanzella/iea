#include "server.hpp"
#include "team.hpp"
#include "session.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

void server::start_accept()
{
	session_ptr new_session(new session(io_service_, team_));
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
