#ifndef _SERVER_SERVER_HPP_
#define _SERVER_SERVER_HPP_
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <list>
#include <vector>
#include "team.hpp"
#include "session.hpp"
#include "bot.hpp"

class session;
class Bot;
typedef boost::shared_ptr<session> session_ptr;

class server
{
	friend class Bot; // Friend, so Bot can access server's private members
	public:
		server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint);

		void start_accept();
		void handle_accept(session_ptr, const boost::system::error_code&);
		
		Team& team_with_id(int id);

	private:
		boost::asio::io_service& io_service_;
		boost::asio::ip::tcp::acceptor acceptor_;
		std::vector<Team> teams_;
		std::vector<session_ptr> sessions_;
		Bot gamemaster;
};

typedef boost::shared_ptr<server> server_ptr;
typedef std::list<server_ptr> server_list;
#endif /* _SERVER_SERVER_HPP_ */
