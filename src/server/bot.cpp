#include <fstream>
#include <string>
#include <vector>
#include "bot.hpp"
#include "question.hpp"

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
