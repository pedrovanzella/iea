#include <set>
#include "team.hpp"
#include "player.hpp"
#include <boost/bind.hpp>

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
	_score++;
}

/* Aceita um novo jogador no time */
void Team::join(player_ptr player)
{
	players_.insert(player); /* coloca ele no vetor de jogadores */
	std::for_each(recent_msgs_.begin(), recent_msgs_.end(), /* E entrega as mensagens recentes pra ele */
			boost::bind(&Player::deliver, player, _1));
}

/* Entrega as mensagens para todos os jogadores do time */
void Team::deliver(const message& msg)
{
	recent_msgs_.push_back(msg);
	while (recent_msgs_.size() > max_recent_msgs)
		recent_msgs_.pop_front();

	std::for_each(players_.begin(), players_.end(), /* Envia as mensagens para todos os jogadores, através de sua sessão */
			boost::bind(&Player::deliver, _1, boost::ref(msg)));
}

/* Tira um jogador do time */
void Team::leave(player_ptr player)
{
	players_.erase(player);
}
