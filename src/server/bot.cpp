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


void Bot::ask()
{
	Question q = questions_[std::rand() % questions_.size()];
	last_question_asked = q;
	/* Send question to all teams in server */
}

