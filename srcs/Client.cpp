#include "Server.hpp"

Client::Client(int sd, std::string address)
{
	socket = sd;
	this->client_address = address;
}

int		Client::getSD()
{
	return (this->socket);
}

Client &Client::operator=(const Client& Other)
{
		this->socket = Other.socket;
		this->client_address = Other.client_address;
		this->option_buffer = Other.option_buffer;
		this->request = Other.request;
		return (*this);
}

Client::~Client(){}
