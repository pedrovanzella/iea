#include "player.hpp"

Player::Player()
{
	_score = 0;
}

Player::Player(int id)
{
	_score = 0;
	_id = id;
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

const int Player::id() const
{
	return _id;
}

int Player::id()
{
	return _id;
}
