#include <fstream>
#include <string>
#include <vector>
#include <thread>
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
	load_questions();
	// Cria uma thread por team, passa uma referência pro team pra thread
	for (auto i : server_->teams_) {
		team_threads_.push_back(std::thread([i, this](){
					while(true) {
						/* Run game here */
						Question q = this->questions_[rand() % this->questions_.size()]; // Random question selected. There is a better way.
						std::cout << "[" << i.id() << "] " << q.description() << std::endl;
					}
					}));
	}

	for (auto& t : team_threads_) {
		t.join(); 
	}
}
