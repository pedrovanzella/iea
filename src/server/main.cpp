#include <iostream>
#include <fstream>
#include <vector>
#include "question.hpp"
#include "main.hpp"

using std::cout;
using std::cin;
using std::string;
using std::endl;
using std::vector;
using std::ifstream;
using std::getline;

int main(int argc, char** argv)
{
	cout << "Init server" << endl;

	vector<Question> questions;

	cout << "Loading questions" << endl;
	load_questions(questions);

	for(vector<Question>::iterator i = questions.begin(); i != questions.end(); i++) {
		cout << "Question: " << i->description() << endl << "\tAnswer: " << i->answer() << endl << endl;
	}

	return EXIT_SUCCESS;
}

void load_questions(vector<Question>& questions)
{
	ifstream infile;
	infile.open("questionsdb", ifstream::in);

	string newquestion;
	while(getline(infile, newquestion)) {
	    Question q(newquestion);
	    questions.push_back(q);
	}
}
