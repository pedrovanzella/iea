#include "player.hpp"

Player::Player()
{
	_score = 0;
}

const int Player::score() const
{
	return _score;
}

int Player::score()
{
	return _score;
}

void Player::increase_score()
{
	_score++;
}
