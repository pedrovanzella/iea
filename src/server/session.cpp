#include "session.hpp"
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;

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
