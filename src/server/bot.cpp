#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "bot.hpp"
#include "question.hpp"
#include "server.hpp"
#include "team.hpp"

using std::ifstream;
using std::string;

void Bot::load_questions()
{
	ifstream infile;
	infile.open("questionsdb", ifstream::in);

	string newquestion;
	while(getline(infile, newquestion)) {
	    Question q(newquestion);
	    questions_.push_back(q);
	}
}


void Bot::run()
{
	std::cout << "Loading questions" << std::endl;
	load_questions();
	std::cout << "Questions loaded" << std::endl;
	// Cria uma thread por team, passa uma referência pro team pra thread

}
