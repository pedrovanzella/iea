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
	std::vector<Player>::iterator i;
	for (i = _players.begin(); i != _players.end(); i++) {
		if (i->id() == p.id()) { /* TODO: Overload == in Player */
			_players.erase(i);
			return;
		}
	}
	/* TODO: Throw exception if we get here, there were no player p in _players */
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
