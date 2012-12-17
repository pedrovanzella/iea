#include "client.hpp"
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include "../shared/message.hpp"

/* Construtor do cliente. Responsável por conectá-lo ao servidor */
client::client(boost::asio::io_service& io_service, tcp::resolver::iterator endpoit_iterator) : io_service_(io_service), socket_(io_service)
{
	boost::asio::async_connect(socket_, endpoit_iterator,
			boost::bind(&client::handle_connect, this, /* Chama a Handle Connect ao iniciar a conexão */
				boost::asio::placeholders::error));
}

/* Coloca uma mensagem na fila de escrita */
void client::write(const message& msg)
{
	io_service_.post(boost::bind(&client::do_write, this, msg));
}

/* Encerra a conexão com o servidor */
void client::close()
{
	io_service_.post(boost::bind(&client::do_close, this));
}

/* Caso não tenha nenhum erro na conexão, cria um socket para o servidor */
void client::handle_connect(const boost::system::error_code& error)
{
	if (!error) {
		boost::asio::async_read(socket_, /* Fica lendo mensagens */
			boost::asio::buffer(read_msg_.data(), message::header_length),
			boost::bind(&client::handle_read_header, this, /* Se der erro, chama esta função */
				boost::asio::placeholders::error));
	}
}

/* Responsável por avaliar os headers da mensagem */
void client::handle_read_header(const boost::system::error_code& error)
{
	if (!error && read_msg_.decode_header()) { /* Se não deu erro e conseguiu decodificar os headers */
		boost::asio::async_read(socket_,
				boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
				boost::bind(&client::handle_read_body, this, /* Então lê a mensagem */
					boost::asio::placeholders::error));
	} else {
		do_close(); /* Se deu erro, fecha a conexão */
	}
}

/* Lê o corpo da mensagem e faz algo com ele */
void client::handle_read_body(const boost::system::error_code& error)
{
	if (!error) {
		std::cout.write(read_msg_.body(), read_msg_.body_length()); /* No caso, imprime na stdout */
		std::cout << "\n";
		boost::asio::async_read(socket_, /* E volta a esperar uma mensagem nova */
				boost::asio::buffer(read_msg_.data(), message::header_length),
				boost::bind(&client::handle_read_header, this,
					boost::asio::placeholders::error));
	} else {
		do_close();
	}
}

/* Escreve a mensagem no socket */
void client::do_write(message msg)
{
	bool write_in_progress = !write_msgs_.empty();
	write_msgs_.push_back(msg);
	if (!write_in_progress) {
		boost::asio::async_write(socket_,
				boost::asio::buffer(write_msgs_.front().data(),
					write_msgs_.front().length()),
				boost::bind(&client::handle_write, this,
					boost::asio::placeholders::error));
	}
}

/* Tira uma mensagem da fila de escrita para ser enviada */
void client::handle_write(const boost::system::error_code& error)
{
	if (!error) {
		write_msgs_.pop_front();
		if (!write_msgs_.empty()) {
			boost::asio::async_write(socket_,
					boost::asio::buffer(write_msgs_.front().data(),
						write_msgs_.front().length()),
					boost::bind(&client::handle_write, this,
						boost::asio::placeholders::error));
		}
	} else {
		do_close();
	}
}

/* Encerra a conexão, matando o socket */
void client::do_close()
{
	socket_.close();
}
