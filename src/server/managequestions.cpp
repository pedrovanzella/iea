#include <iostream>
#include <vector>
#include <fstream>
#include "question.hpp"
#include "main.hpp"

using std::vector;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;
using std::string;

void add_question_to_db(vector<Question>& questions, Question& q)
{
	questions.push_back(q);

	ofstream outfile;

	outfile.open("questionsdb", ofstream::app);
	outfile << q;
}

int main(int argc, char** argv)
{
	vector<Question> questions;
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
