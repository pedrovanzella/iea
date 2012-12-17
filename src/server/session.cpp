#include "session.hpp"
#include "server.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

using boost::asio::ip::tcp;
using std::cout;
using std::endl;
using std::string;

/* Construtor da sessão inicia a mesma com uma referência para o socket, o time e o servidor correspondente da mesma */
session::session(boost::asio::io_service& io_service, Team& team, server* s) 
	: socket_(io_service), team_(team)
{
   server_ = s;
}


/* Retorna o socket associado à sessão */
tcp::socket& session::socket()
{
	return socket_;
}

/* Inicia a sessão */
void session::start()
{
	team_.join(shared_from_this()); /* Entra no time */
	boost::asio::async_read(socket_, /* E fica esperando assincronamente por uma mensagem */
			boost::asio::buffer(read_msg_.data(), message::header_length),
			boost::bind(
				&session::handle_read_header, shared_from_this(), /* Quando receber a mensagem, decodifica o header */
				boost::asio::placeholders::error));
}

/* Entrega a mensagem para esta sessão */
void session::deliver(const message& msg)
{
    bool write_in_progress = !write_msgs_.empty();
    write_msgs_.push_back(msg);
	if (!write_in_progress)
    {
		boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()),
				boost::bind(&session::handle_write, shared_from_this(),
					boost::asio::placeholders::error));
	}
}

/* Decodifica o header da mensagem */
void session::handle_read_header(const boost::system::error_code& error)
{
	if (!error && read_msg_.decode_header())
	{
		boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				boost::bind(&session::handle_read_body, shared_from_this(), /* Se deu tudo certo, lê o corpo */
					boost::asio::placeholders::error));
	}
	else /* Se deu erro, sai do time */
	{
		team_.leave(shared_from_this());
	}
}

/* Lê o corpo da mensagem */
void session::handle_read_body(const boost::system::error_code& error)
{
	if (!error)
	{
		parse_message_for_commands(read_msg_); /* O que temos na mensagem? */
		team_.deliver(read_msg_); /* Entrega a mensagem para todo o time */
		boost::asio::async_read(socket_, /* E volta a esperar por mensagens */
				boost::asio::buffer(read_msg_.data(), message::header_length),
				boost::bind(&session::handle_read_header, shared_from_this(),
					boost::asio::placeholders::error));
	}
	else
	{
		team_.leave(shared_from_this()); /* Se der erro, sai do time */
	}
}

/* Escreve a mensagem no socket */
void session::handle_write(const boost::system::error_code& error)
{
	if (!error)
	{
		write_msgs_.pop_front();
		if (!write_msgs_.empty())
		{
			boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().data(),
						write_msgs_.front().length()),
					boost::bind(&session::handle_write, shared_from_this(),
						boost::asio::placeholders::error));
		}
	}
	else
	{
		team_.leave(shared_from_this());
	}
}

/* Verifica se temos um comando ou uma mensagem normal */
void session::parse_message_for_commands(message& msg)
{
	string cmd(msg.body(), msg.body_length());

	if (cmd[0] == '/') { /* Comandos começam com '/' */
		cout << cmd << endl;
		switch (cmd[1]) {
			case 't': /* Comando para mudar de time */
			case 'T':
				team_.leave(shared_from_this()); /* sai do time atual */
				team_ = server_->team_with_id(std::atoi(&cmd[3])); /* informa para o servidor que entramos em um novo time */
				team_.join(shared_from_this()); /* entra no novo time */
		}
	} else { // Temos a resposta certa?
		// Se sim, desbloqueia o mutex
		// team_thread_mutex_[teamid].unlock()
	}
}
