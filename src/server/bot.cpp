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
	std::cout << "Loading questions" << std::endl;
	load_questions();
	std::cout << "Questions loaded" << std::endl;
	// Cria uma thread por team, passa uma referência pro team pra thread
	for (auto i : server_->teams_) {
		team_threads_.push_back(std::thread([i, this](){
					std::mutex m;
					//team_thread_mutex_.push_back(m);
					while(true) {
						/* Run game here */
						Question q = this->questions_[rand() % this->questions_.size()]; // Random question selected. There is a better way.
						std::cout << "[" << i.id() << "] " << q.description() << std::endl;
						// Send question out
						m.lock(); // Will be unlocked by some session
					}
					}));
	}

	for (auto& t : team_threads_) {
		t.join(); 
	}
}
