#include "Server.hpp"
#include "General.hpp"

Server::Server(Config config)
{std::cout << "\033[0;35m\e[1mServer constructor\e[0m\033[0m" << std::endl;
	for (std::list<Config::server>::iterator i = config.getServers().begin(); i != config.getServers().end(); i++)
		sub_serv.push_back(SubServ(*i, this));
}

Server::Server(Server &Other)
{
	this->readfds = Other.readfds;
	this->writefds = Other.writefds;
	this->sub_serv = Other.sub_serv;
	this->max_sd = Other.max_sd;
}

void Server::accept_connection(SubServ &s_srv)
{
	sockaddr_in client;
	socklen_t size = sizeof(client);
	int new_sd;
	if ((new_sd = accept(s_srv.getSD(), (sockaddr *)&client, &size)) < 0)
	{
		if (errno != EWOULDBLOCK)
			throw ServerException("Accept Failed");
		return ;
	}
	s_srv.setClientList(Client(new_sd, ipbytes_to_ipv4(client.sin_addr)));
	if (new_sd > this->max_sd)
		this->max_sd = new_sd;
}

void Server::UpAndDownLoad(SubServ &s_srv)
{	
	//si FD_ISSET(sd_serv, read_fd) = true
	// accepter connection, add socket a liste des scokets des clients
	if (FD_ISSET(s_srv.getSD(), &readfds))
		accept_connection(s_srv);
	//on recup la liste de sd des clients et on itere dessus
	//si FD_ISSET(sd_client, writefds)
	for (std::list<Client>::iterator i = s_srv.getClientList().begin(); i != s_srv.getClientList().end(); i++)
	{
		if (FD_ISSET((*i).getSD(), &writefds))
			;
			// read ce que le client a envoyer tant que != \r\n
			// traiter la requete
	}
}

static void getUpAndDownLoad(SubServ &s_srv)
{
	s_srv.getMainServer().UpAndDownLoad(s_srv);
}

void	Server::listen_it()
{
	fd_set	server_read_fd;
	 //biggest fd in the set

	FD_ZERO(&server_read_fd);
	for (std::list<SubServ>::iterator i = sub_serv.begin(); i != sub_serv.end(); i++)
	{
		FD_SET((*i).getSD(), &server_read_fd);
		max_sd = (*i).getSD();
	}
	for (;"ever";)
	{//boucle infinie
		readfds = server_read_fd;
		FD_ZERO(&writefds);
		try
		{
			if (select(max_sd + 1, &readfds, &writefds, NULL, NULL) < 0 && errno!=EINTR)
				ServerException("Select Failed");
			//iterer sur chaque SD de chaque sub_serv
			std::for_each(sub_serv.begin(), sub_serv.end(), getUpAndDownLoad);
		}
		catch (const std::exception& e)
		{
			throwError(e);
		}
	}
}

Server &Server::operator=(const Server& Other)
{
	this->readfds = Other.readfds;
	this->writefds = Other.writefds;
	this->sub_serv = Other.sub_serv;
	this->max_sd = Other.max_sd;
	return (*this);
}


Server::~Server()
{std::cout << "\033[0;35m\e[1mServer destructor\e[0m\033[0m" << std::endl;
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