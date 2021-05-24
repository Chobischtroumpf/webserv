#include "Server.hpp"

void Socket::createSD(void)
{
	if ((this->sock_des = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw SocketException("Creation of the Socket descriptor failed");
}

void Socket::initAddress(int port)
{
	this->address.sin_family = AF_INET;
	this->address.sin_addr.s_addr = INADDR_ANY;
	this->address.sin_port = htons(port);
}

void Socket::setSockOption()
{
	if (setsockopt(this->sock_des, SOL_SOCKET, SO_REUSEADDR,
		&this->option_buffer, sizeof(this->option_buffer)))
		throw SocketException("setting socket options failed");
}

Socket::Socket(Config::server serv)
{
	this->server_conf = serv;
	createSD();
	initAddress(serv.port);
}

void Socket::setSocketNonBlock()
{
	if (fcntl(this->sock_des, F_SETFL, O_NONBLOCK) < 0)
		throw SocketException("Setting Socket to nonblocking");
}

int				Socket::getSD()
{
	return(this->sock_des);
}
		
sockaddr_in		Socket::getAddress()
{
	return(this->address);
}
		
Config::server	Socket::getConf()
{
	return(this->server_conf);
}
		
Socket::~Socket(){}
		