#ifndef _SERVER_TEAM_HPP_
#define _SERVER_TEAM_HPP_
#include "player.hpp"
#include <vector>

class Team
{
	private:
		std::vector<Player> _players;
		int _id;
		int _score;

	public:
		Team();
		Team(int id);

		const std::vector<Player> players() const;

		void add_player(const Player&);
		void remove_player(const Player&);

		const int id() const;
		int id();

		const int score() const;
		int score();

		void increase_score();
};

#endif /* _SERVER_TEAM_HPP_ */
