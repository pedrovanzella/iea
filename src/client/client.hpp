#ifndef _CLIENT_CLIENT_HPP_
#define _CLIENT_CLIENT_HPP_

#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "../shared/message.hpp"

using boost::asio::ip::tcp;

typedef std::deque<message> message_queue; /* Also defined in message.hpp, may not be needed */

class client
{
	public:
		client(boost::asio::io_service&, tcp::resolver::iterator);

		void write(const message&);
		void close();

	private:
		void handle_connect(const boost::system::error_code&);
		void handle_read_header(const boost::system::error_code&);
		void handle_read_body(const boost::system::error_code&);
		void do_write(message);
		void handle_write(const boost::system::error_code&);
		void do_close();

	private:
		boost::asio::io_service& io_service_;
		tcp::socket socket_;
		message read_msg_;
		message_queue write_msgs_;
};

#endif /* _CLIENT_CLIENT_HPP_ */
