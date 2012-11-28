#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

class Player
{
	private:
		int _score;

	public:
		const int score() const;
		int score();

		void increase_score();

		Player();
};

#endif /* _PLAYER_HPP_ */
