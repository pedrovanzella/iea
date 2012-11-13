#include <boost/asio.hpp>
#include <iostream>
#include "question.hpp"

int main(int argc, char** argv)
{
	boost::asio::io_service io_service;

	std::cout << "Init server" << std::endl;

	Question *q = new(Question);
	q->set_description("A long time ago, in a galaxy far away...");
	q->set_answer("Star Wars");

	std::cout << "Question: " << "[" << q->description() << "]" << std::endl;
	std::cout << "Answer: " << "[" << q->answer() << "]" << std::endl;

	return EXIT_SUCCESS;
}
