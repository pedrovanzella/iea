#include <vector>
#include "team.hpp"
#include "player.hpp"

Team::Team()
{
	_id = 0;
	_score = 0;
}

Team::Team(int id)
{
	_id = id;
	_score = 0;
}

const std::vector<Player> Team::players() const
{
	return _players;
}

void Team::add_player(const Player& p)
{
	_players.push_back(p);
}

void Team::remove_player(const Player& p)
{
	// TODO
}

const int Team::id() const
{
	return _id;
}

int Team::id()
{
	return _id;
}

const int Team::score() const
{
	return _score;
}

int Team::score()
{
	return _score;
}

void Team::increase_score()
{
	_score++;
}
