#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "question.hpp"

/* Private functions */
void load_questions(std::vector<Question>& questions);
void add_question_to_db(std::vector<Question>& questions, Question& q);

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;
using std::ifstream;

int main(int argc, char** argv)
{
	boost::asio::io_service io_service;

	cout << "Init server" << endl;

	vector<Question> questions;

	cout << "Loading questions" << endl;
	load_questions(questions);

	cout << "Add new question:" << endl;
	cout << "Question: ";
	string desc;
	getline(cin, desc);
	cout << "Answer: ";
	string ans;
	getline(cin, ans);
	Question q(desc, ans);
	add_question_to_db(questions, q);

	return EXIT_SUCCESS;
}

void load_questions(vector<Question>& questions)
{
	ifstream infile;

	infile.open("questionsdb", ifstream::in);
}

void add_question_to_db(vector<Question>& questions, Question& q)
{
	/* Segfaulting here */
	questions.push_back(q);

	std::ofstream outfile;

	outfile.open("questionsdb", std::ofstream::app);
	outfile << q.description() << endl << q.answer();
}
