#ifndef _SERVER_TEAM_HPP_
#define _SERVER_TEAM_HPP_
#include "player.hpp"
#include "../shared/message.hpp"
#include <set>

class Team
{
	private:
		int _id;
		int _score;
		std::set<player_ptr> players_;
		enum { max_recent_msgs = 100 };
		message_queue recent_msgs_;

	public:
		Team();
		Team(int id);

		//explicit Team(const Team&);
		//explicit Team(Team&);

		//Team& operator=(Team&);
		//Team& operator=(const Team&);



		void set_score(int);
		void set_id(int);

		void join(player_ptr);
		void leave(player_ptr);

		void deliver(const message&);

		const int id() const;
		int id();

		const int score() const;
		int score();

		void increase_score();
};

#endif /* _SERVER_TEAM_HPP_ */
