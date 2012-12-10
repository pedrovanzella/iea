#include <set>
#include "team.hpp"
#include "player.hpp"
#include <boost/bind.hpp>
#include <thread>

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
	m.lock();
	_score++;
	m.unlock();
}

void Team::join(player_ptr player)
{
	players_.insert(player);
	std::for_each(recent_msgs_.begin(), recent_msgs_.end(),
			boost::bind(&Player::deliver, player, _1));
}

void Team::deliver(const message& msg)
{
	recent_msgs_.push_back(msg);
	while (recent_msgs_.size() > max_recent_msgs)
		recent_msgs_.pop_front();

	std::for_each(players_.begin(), players_.end(),
			boost::bind(&Player::deliver, _1, boost::ref(msg)));
}

void Team::leave(player_ptr player)
{
	players_.erase(player);
}
