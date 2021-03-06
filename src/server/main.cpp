#include <iostream>
#include <fstream>
#include <vector>
#include <boost/asio.hpp>
#include "question.hpp"
#include "server.hpp"
#include "main.hpp"

using std::cout;
using std::cin;
using std::cerr;
using std::string;
using std::endl;
using std::vector;
using std::ifstream;
using std::getline;
using std::atoi;
using boost::asio::ip::tcp;

int main(int argc, char** argv)
{
	try {
		if (argc < 2) {
			cerr << "Usage: " << argv[0] << " <port> [<port> ...]" << endl;
			return 1;
		}
		cout << "Init server" << endl << endl;

		boost::asio::io_service io_service;
		server_list servers;
		for (int i = 1; i < argc; ++i) {
			tcp::endpoint endpoint(tcp::v4(), atoi(argv[i]));
			server_ptr srvr(new server(io_service, endpoint));
			servers.push_back(srvr);
		}

		io_service.run();
	} catch (std::exception& e) {
		cerr << "FAIL: " << e.what() << endl;
	}

	return EXIT_SUCCESS;
}
