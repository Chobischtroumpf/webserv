#include "Server.hpp"

Server::Server(std::string file)
{
	int opt = 0;
	struct protoent *protocol = NULL;

	this->address.sin_family = AF_INET;
	this->address.sin_addr.s_addr = INADDR_ANY;
	this->address.sin_port = htons(port);
	// std::cout << "socket\n";
	if ((this->sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		std::cout << strerror(errno) << std::endl;
	fcntl(this->sock_fd, F_SETFL, O_NONBLOCK);
	if ((protocol = getprotobyname("tcp")) == NULL)
		exit(-1);
	// if (setsockopt(this->sock_fd, protocol->p_proto, IPV6_V6ONLY, &opt, sizeof(opt)))
	// 	std::cout << "1 " << strerror(errno) << std::endl;
	opt = 1;
	// std::cout << "setsockopt2\n";
	if (setsockopt(this->sock_fd, protocol->p_proto, SO_REUSEADDR, &opt, sizeof(opt)))
		std::cout << "2" << strerror(errno) << std::endl;
	// std::cout << "bind\n";
	if (bind(this->sock_fd, (struct sockaddr *)&this->address,
		sizeof(this->address))<0)
		std::cout << strerror(errno) << std::endl;
	// std::cout << "listen\n";
	if (listen(this->sock_fd, 128) < 0)
		std::cout << strerror(errno) << std::endl;
}

// Message					Server::check_request(std::queue<std::string> input)
// {

// }

// Message					*Server::check_time_out(std::map<size_t, User>)
// {

// }

// void						Server::display_users(std::string mode = "all")
// {

// }

// void						Server::display_user(size_t id)
// {

// }

// void						Server::display_chans()
// {

// }

// void						Server::display_chan(size_t id)
// {

// }

void						Server::add_user(User neo)
{	
	this->usr_lst[neo.get_sock_fd_id()] = neo;	
}

void						Server::add_channel(Channel neo)
{
	this->chan_lst[neo.get_id()] = neo;
}

void						Server::delete_user(size_t id)
{
	this->usr_lst.erase(id);
}

void						Server::delete_channel(size_t id)
{
	this->chan_lst.erase(id);
}

fd_set						Server::get_readfds()
{
	return(this->readfds);
}

sockaddr_in						Server::get_addr()
{
	return(this->address);
}

int							Server::get_sock_fd()
{
	return(this->sock_fd);
}

User						*Server::get_user(size_t id)
{
	return(&this->usr_lst[id]);
}

std::map<size_t, User>		*Server::get_users()
{
	return(&this->usr_lst);
}

Channel						*Server::get_chan(size_t id)
{
	return(&this->chan_lst[id]);
}

std::map<size_t, Channel>	*Server::get_channels()
{
	return(&this->chan_lst);
}

std::string					Server::get_pass()
{
	return(this->pass);
}

Server::~Server(){}
