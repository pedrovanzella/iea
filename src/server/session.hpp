#ifndef _SERVER_SESSION_HPP_
#define _SERVER_SESSION_HPP_
#include "player.hpp"
#include "team.hpp"
#include "../shared/message.hpp"
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "server.hpp"

class server;

using boost::asio::ip::tcp;

class session
	: public Player,
	  public boost::enable_shared_from_this<session>
{
	public:
		session(boost::asio::io_service&, Team&, server*);
		tcp::socket& socket();
		
		void start();
		void deliver(const message&);

		void handle_read_header(const boost::system::error_code&);
		void handle_read_body(const boost::system::error_code&);
		void handle_write(const boost::system::error_code&);

		void parse_message_for_commands(message&);
	private:
		tcp::socket socket_;
		Team& team_;
		message read_msg_;
		message_queue write_msgs_;
		server* server_;
};

typedef boost::shared_ptr<session> session_ptr;

#endif /* _SERVER_SESSION_HPP */
