#include "Server.hpp"
#include "General.hpp"

///////////////////////////////////
///	Constructor and Destructors ///
///////////////////////////////////

Server::Server()
{
	keep_going = true;
	this->timeout.tv_sec = 1;
	this->timeout.tv_usec = 0;
}

Server::Server(Config config)
{
	DEBUG("##### SERVER INIT #####")
	for (std::list<Config::server>::iterator i = config.getServers().begin(); i != config.getServers().end(); i++)
		sub_serv.push_back(SubServ(*i, this));
	keep_going = true;
	this->timeout.tv_sec = 1;
	this->timeout.tv_usec = 0;
}

Server::Server(Server &Other)
{
	this->readfds = Other.readfds;
	this->writefds = Other.writefds;
	this->sub_serv = Other.sub_serv;
	this->max_sd = Other.max_sd;
	this->keep_going = true;
	this->timeout= Other.timeout;
}

Server::~Server()
{
	sub_serv.clear();
}


///////////////////////////////////
///			  Methods			///
///////////////////////////////////

std::list<Client *>::iterator	Server::removeClient(std::list<Client *>::iterator &client, SubServ &sub_srv)
{
	std::list<Client *>::iterator tmp;
	FD_CLR((*client)->getSocketDesc(), &server_read_fd);
	FD_CLR((*client)->getSocketDesc(), &server_write_fd);
	close((*client)->getSocketDesc());
	delete (*client);
	tmp = sub_srv.getClientList().erase(client);
	return (tmp);
}

void Server::checkConnections(void)
{
	char c[1];
	for (std::list<SubServ>::iterator subserv_it = this->sub_serv.begin();
			subserv_it != this->sub_serv.end(); subserv_it++)
	{
		for (std::list<Client *>::iterator client_it = (*subserv_it).getClientList().begin();
				 client_it != (*subserv_it).getClientList().end(); client_it++)
		{
			if (recv((*client_it)->getSocketDesc(), c, 1, MSG_PEEK) == 0)
			{
				close((*client_it)->getSocketDesc());
				(*subserv_it).popClient((*client_it));
				FD_CLR((*client_it)->getSocketDesc(), &server_read_fd);
				FD_CLR((*client_it)->getSocketDesc(), &server_write_fd);
			}
		}
	}
}

void Server::acceptConnection(SubServ &s_srv)
{
	//DEBUG("acceptConnection")
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
	s_srv.setClientList(new Client(new_sd, ipBytesToIpv4(client.sin_addr)));
	if (new_sd > this->max_sd)
		this->max_sd = new_sd;
	FD_SET(new_sd, &server_read_fd);
	FD_SET(new_sd, &server_write_fd);
}

void Server::upAndDownLoad(SubServ &sub_srv)
{
	if (FD_ISSET(sub_srv.getSocketDesc(), &readfds))
		acceptConnection(sub_srv);
	std::list<Client *>::iterator client = sub_srv.getClientList().begin();
	while(client != sub_srv.getClientList().end())
	{
		if (FD_ISSET((*client)->getSocketDesc(), &writefds) && (*client)->requestReceived() == true)
		{
			Request test = Request((*client)->getRequest(), sub_srv.getConf());
			(*client)->sendRequest(test);
			client = removeClient(client, sub_srv);
		}
		if (client != sub_srv.getClientList().end() && FD_ISSET((*client)->getSocketDesc(), &readfds))
		{
			int ret_val;
			if ((ret_val = (*client)->receiveRequest()) < 0)
			{
				DEBUG("--> deleting client")
				client = removeClient(client, sub_srv);
			}
			else if (ret_val == 0)
			{
				(*client)->setReceived(true);
			}
		}
		if (*client)
			client++;
	}
}

static void getUpAndDownLoad(SubServ &s_srv)
{
	s_srv.getMainServer().upAndDownLoad(s_srv);
}

void	Server::listenIt()
{
	DEBUG("##### SERVER LISTENING #####")
	FD_ZERO(&server_read_fd);
	for (std::list<SubServ>::iterator i = sub_serv.begin(); i != sub_serv.end(); i++)
	{
		FD_SET((*i).getSocketDesc(), &server_read_fd);
		max_sd = (*i).getSocketDesc(); //what if the last subserv as a smaller sd ?
	}
	FD_COPY(&server_read_fd, &readfds);
	int ret_sel = 1;
	while(keep_going)
	{
		FD_ZERO(&writefds);
		FD_COPY(&server_read_fd, &readfds);
		FD_COPY(&server_write_fd, &writefds);
		try
		{	
			if ((ret_sel = select(max_sd + 1, &readfds, &writefds, NULL, NULL/*&timeout*/)) < 0 && errno!=EINTR)
				ServerException("Select Failed");
			else 
			{
				std::for_each(sub_serv.begin(), sub_serv.end(), getUpAndDownLoad);
			}
		}
		catch (const std::exception& e)
		{
			throwError(e);
		}
	}
}

///////////////////////////////////
///			Overloads			///
///////////////////////////////////

Server &Server::operator=(const Server& Other)
{
	this->readfds = Other.readfds;
	this->writefds = Other.writefds;
	this->sub_serv = Other.sub_serv;
	this->max_sd = Other.max_sd;
	return (*this);
}

