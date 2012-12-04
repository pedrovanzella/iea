#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "../shared/message.hpp"
#include "client.hpp"

using std::cout;
using std::endl;
using std::cerr;
using std::cin;
using std::strlen;
using std::memcpy;
using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
	try {
		if (argc != 3) {
			cerr << "Usage: " << argv[0] << " <host> <port>" << endl;
			return 1;
		}

		cout << "Init client" << endl;
		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(argv[1], argv[2]);
		tcp::resolver::iterator iterator = resolver.resolve(query);

		client c(io_service, iterator);

		boost::thread t(boost::bind(&boost::asio::io_service::run, &io_service));

		char line[message::max_body_length + 1];
		while (cin.getline(line, message::max_body_length + 1)) {
			message msg;
			msg.body_length(strlen(line));
			memcpy(msg.body(), line, msg.body_length());
			msg.encode_header();
			c.write(msg);
		}

		c.close();
		t.join();
	} catch (std::exception& e) {
		cerr << "FAIL: " << e.what() << endl;
	}
	return EXIT_SUCCESS;
}
