#include "Server.hpp"
#include "General.hpp"

Server::Server(Config config)
{
	for (std::list<Config::server>::iterator i = config.getServers().begin(); i != config.getServers().end(); i++)
		sub_serv.push_back(Socket(*i));
}

Server::~Server()
{
	sub_serv.clear();
}


// int opt = 0;
// 	struct protoent *protocol = NULL;

// 	this->address.sin_family = AF_INET;
// 	this->address.sin_addr.s_addr = INADDR_ANY;
// 	this->address.sin_port = htons(port);
// 	// std::cout << "socket\n";
// 	if ((this->sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
// 		std::cout << strerror(errno) << std::endl;
// 	fcntl(this->sock_fd, F_SETFL, O_NONBLOCK);
// 	if ((protocol = getprotobyname("tcp")) == NULL)
// 		exit(-1);
// 	// if (setsockopt(this->sock_fd, protocol->p_proto, IPV6_V6ONLY, &opt, sizeof(opt)))
// 	// 	std::cout << "1 " << strerror(errno) << std::endl;
// 	opt = 1;
// 	// std::cout << "setsockopt2\n";
// 	if (setsockopt(this->sock_fd, protocol->p_proto, SO_REUSEADDR, &opt, sizeof(opt)))
// 		std::cout << "2" << strerror(errno) << std::endl;
// 	// std::cout << "bind\n";
// 	if (bind(this->sock_fd, (struct sockaddr *)&this->address,
// 		sizeof(this->address))<0)
// 		std::cout << strerror(errno) << std::endl;
// 	// std::cout << "listen\n";
// 	if (listen(this->sock_fd, 128) < 0)
// 		std::cout << strerror(errno) << std::endl;