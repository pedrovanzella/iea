#ifndef _PLAYER_HPP_
#define _PLAYER_HPP_

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
};

#endif /* _PLAYER_HPP_ */
