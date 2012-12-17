#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

#include <boost/shared_ptr.hpp>
#include "../shared/message.hpp"

class Player
{
	private:
		int _score;
		int _id;

	public:
		const int score() const;
		int score();

		const int id() const;
		int id();

		void increase_score();

		Player();
		Player(int id);

		virtual ~Player() {}
		virtual void deliver(const message& msg) = 0; /* Implementado na sessão */
};

typedef boost::shared_ptr<Player> player_ptr;

#endif /* _PLAYER_HPP_ */
