#include "session.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;
using std::cout;
using std::endl;
using std::string;

session::session(boost::asio::io_service& io_service, Team& team, server* s) 
	: socket_(io_service), team_(team)
{
   server_ = s;
}


tcp::socket& session::socket()
{
	return socket_;
}

void session::start()
{
	team_.join(shared_from_this());
	boost::asio::async_read(socket_,
			boost::asio::buffer(read_msg_.data(), message::header_length),
			boost::bind(
				&session::handle_read_header, shared_from_this(),
				boost::asio::placeholders::error));
}

void session::deliver(const message& msg)
{
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
	if (!write_in_progress)
    {
		boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()),
				boost::bind(&session::handle_write, shared_from_this(),
					boost::asio::placeholders::error));
	}
}

void session::handle_read_header(const boost::system::error_code& error)
{
	if (!error && read_msg_.decode_header())
	{
		boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				boost::bind(&session::handle_read_body, shared_from_this(),
					boost::asio::placeholders::error));
	}
	else
	{
		team_.leave(shared_from_this());
	}
}

void session::handle_read_body(const boost::system::error_code& error)
{
	if (!error)
	{
		parse_message_for_commands(read_msg_);
		team_.deliver(read_msg_);
		boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.data(), message::header_length),
				boost::bind(&session::handle_read_header, shared_from_this(),
					boost::asio::placeholders::error));
	}
	else
	{
		team_.leave(shared_from_this());
	}
}

void session::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{
		write_msgs_.pop_front();
		if (!write_msgs_.empty())
		{
			boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().data(),
						write_msgs_.front().length()),
					boost::bind(&session::handle_write, shared_from_this(),
						boost::asio::placeholders::error));
		}
	}
	else
	{
		team_.leave(shared_from_this());
	}
}

void session::parse_message_for_commands(message& msg)
{
	string cmd(msg.body(), msg.body_length());

	if (cmd[0] == '/') { // All cmds must start with '/'
		cout << cmd << endl;
		switch (cmd[1]) {
			case 't':
			case 'T':
				team_.leave(shared_from_this());
				team_ = server_->team_with_id(std::atoi(&cmd[3]));
				team_.join(shared_from_this());
		}
	} else { // Find out if we got the right answer
		// If so, unlock the mutex;
		// team_thread_mutex_[teamid].unlock()
		// How do we find out the team id from the message?
	}
}
