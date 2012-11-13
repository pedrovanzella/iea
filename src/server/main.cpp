#include <boost/asio.hpp>
#include <iostream>

int main(int argc, char** argv)
{
	boost::asio::io_service io_service;

	std::cout << "Init server" << std::endl;
	return EXIT_SUCCESS;
}
