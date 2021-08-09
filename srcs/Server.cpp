#include "Server.hpp"
#include "General.hpp"

Server::Server()
{DEBUG("Server default constructor")
	keep_going = true;
	this->timeout.tv_sec = 1;
	this->timeout.tv_usec = 0;
}

Server::Server(Config config)
{DEBUG("##### SERVER INIT #####\n")
	for (std::list<Config::server>::iterator i = config.getServers().begin(); i != config.getServers().end(); i++)
		sub_serv.push_back(SubServ(*i, this));
	keep_going = true;
	this->timeout.tv_sec = 1;
	this->timeout.tv_usec = 0;
}

Server::Server(Server &Other)
{DEBUG("Server copy constructor")
	this->readfds = Other.readfds;
	this->writefds = Other.writefds;
	this->sub_serv = Other.sub_serv;
	this->max_sd = Other.max_sd;
	this->keep_going = true;
	this->timeout= Other.timeout;
}

void Server::checkConnections(void)
{
	char c[1];
	for (std::list<SubServ>::iterator subserv_it = this->sub_serv.begin();
			subserv_it != this->sub_serv.end(); subserv_it++)
	{
		for (std::list<Client>::iterator client_it = (*subserv_it).getClientList().begin();
				 client_it != (*subserv_it).getClientList().end(); client_it++)
		{
			if (recv((*client_it).getSocketDesc(), c, 1, MSG_PEEK) == 0)
			{
				close((*client_it).getSocketDesc());
				(*subserv_it).popClient((*client_it));
			}
		}
	}
}

void Server::acceptConnection(SubServ &s_srv)
{DEBUG("acceptConnection")
	sockaddr_in client;
	socklen_t size = sizeof(client);
	int new_sd;
	if ((new_sd = accept(s_srv.getSocketDesc(), (sockaddr *)&client, &size)) < 0)
	{
		if (errno == EBADF)
			return;
		if (errno != EWOULDBLOCK)
			throw ServerException("Accept Failed");
		
		return ;
	}
	Client c = Client(new_sd, ipBytesToIpv4(client.sin_addr));
	s_srv.setClientList(dynamic_cast<Client&>(c));
	if (new_sd > this->max_sd)
		this->max_sd = new_sd;
	FD_SET(new_sd, &server_read_fd);
	FD_SET(new_sd, &server_write_fd);
}

void Server::upAndDownLoad(SubServ &sub_srv)
{DEBUG("upAndDownLoad")	
	//si FD_ISSET(sd_serv, read_fd) = true
	// accepter connection, add socket a liste des sockets des clients
	std::cout << "subserv socket : " << FD_ISSET(sub_srv.getSocketDesc(), &readfds) << std::endl;
	if (FD_ISSET(sub_srv.getSocketDesc(), &readfds))
		acceptConnection(sub_srv);
	sub_srv.printSubserv();
	FD_COPY(&server_read_fd, &readfds);
	//on recup la liste de sd des clients et on itere dessus
	//si FD_ISSET(sd_client, writefds)
	for (std::list<Client>::iterator client = sub_srv.getClientList().begin(); client != sub_srv.getClientList().end(); client++)
	{
		DEBUG("DEBUT DE L'ENQUETE")
		std::cout << (FD_ISSET((*client).getSocketDesc(), &readfds));
		if (FD_ISSET((*client).getSocketDesc(), &writefds) && (*client).requestReceived() == true)
		{
			DEBUG("PARSE HEADER")
			//parsing header
		}
		//recup ce que le client a envoyé
		if (FD_ISSET((*client).getSocketDesc(), &readfds))
		{
			DEBUG("		received request")
			int ret_val;
			if ((ret_val = (*client).receiveRequest()) < 0)
			{//si on recoit -1 > pop le client de la liste, il n'est plus connecter au serveur
				close((*client).getSocketDesc());
				client = sub_srv.getClientList().erase(client);
				//remove from fd_set
			}
			else if (ret_val == 0)//indiquer qu'on a recu qqchose
			{
				(*client).setReceived(true);
			}
			(*client).printClient();
		}
	}
}

static void getUpAndDownLoad(SubServ &s_srv)
{
	s_srv.getMainServer().upAndDownLoad(s_srv);
}

void	Server::listenIt()
{
	DEBUG("##### SERVER LISTENING #####")
	 //biggest fd in the set

	FD_ZERO(&server_read_fd);
	for (std::list<SubServ>::iterator i = sub_serv.begin(); i != sub_serv.end(); i++)
	{
		FD_SET((*i).getSocketDesc(), &server_read_fd);
		max_sd = (*i).getSocketDesc();
	}
	FD_COPY(&server_read_fd, &readfds);
	int ret_sel = 1;
	while(keep_going)
	{//boucle infinie
		FD_ZERO(&writefds);
		DEBUG("boucle");
		try
		{
			DEBUG(ret_sel)
			if ((ret_sel = select(max_sd + 1, &readfds, &writefds, NULL, NULL/*&timeout*/)) < 0 && errno!=EINTR)
				ServerException("Select Failed");
			// else if (ret_sel == 0)
			// {
			// 	DEBUG("before check connections")
				// checkConnections();
			// }
			else //iterer sur chaque SD de chaque sub_serv
				std::for_each(sub_serv.begin(), sub_serv.end(), getUpAndDownLoad);
		}
		catch (const std::exception& e)
		{
			throwError(e);
		}
	}
}

Server &Server::operator=(const Server& Other)
{DEBUG("Server =")
	this->readfds = Other.readfds;
	this->writefds = Other.writefds;
	this->sub_serv = Other.sub_serv;
	this->max_sd = Other.max_sd;
	return (*this);
}


Server::~Server()
{DEBUG("Server destructor")
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