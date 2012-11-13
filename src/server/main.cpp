#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "question.hpp"

/* Private functions */
void load_questions(std::vector<Question*>* questions);
void add_question_to_db(std::vector<Question*>* questions, Question* q);

int main(int argc, char** argv)
{
	boost::asio::io_service io_service;

	std::cout << "Init server" << std::endl;

	std::vector<Question*> *questions = NULL; // God save us all

	std::cout << "Loading questions" << std::endl;
	load_questions(questions);

	std::cout << "Add new question:" << std::endl;
	std::cout << "Question: ";
	char* desc;
	std::cin.getline(desc, 1024);
	std::cout << "Answer: ";
	char* ans;
	std::cin.getline(ans, 1024);
	Question *q = new Question(desc, ans);
	add_question_to_db(questions, q);

	return EXIT_SUCCESS;
}

void load_questions(std::vector<Question*> *questions)
{
	std::ifstream infile;

	infile.open("questionsdb", std::ifstream::in);
}

void add_question_to_db(std::vector<Question*> *questions, Question* q)
{
	questions->push_back(q);

	std::ofstream outfile;

	outfile.open("questionsdb", std::ofstream::app);
	outfile << q;
}
