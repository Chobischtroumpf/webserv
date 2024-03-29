#include "SubServ.hpp"

///////////////////////////////////
///	Constructor and Destructors ///
///////////////////////////////////

SubServ::SubServ(Config::server serv, Server *main_serv):
	main_serv(*main_serv)
{
	DEBUG("##### SUBSERV INIT #####")
	this->server_conf = serv;
	this->option_buffer = 0;
	createSD();
	setSockOption();
	setSubServNonBlock();
	initAddress(serv.port);
	bindSubServ();
	socketListener();
}

SubServ::~SubServ(){
	client_list.clear();
}

///////////////////////////////////
///			  Methods			///
///////////////////////////////////

void SubServ::createSD()
{
	if ((this->sock_desc = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw SubServException("Creation of the SubServ descriptor failed");
}

void SubServ::setSockOption()
{
	if (setsockopt(this->sock_desc, SOL_SOCKET, SO_REUSEADDR,
		&this->option_buffer, sizeof(this->option_buffer)))
		throw SubServException("setting socket options failed");
}

void SubServ::setSubServNonBlock()
{
	if (fcntl(this->sock_desc, F_SETFL, O_NONBLOCK) < 0)
		throw SubServException("Error setting SubServ to nonblocking");
}

void SubServ::initAddress(int port)
{
	this->srv_address.sin_family = AF_INET;
	this->srv_address.sin_addr.s_addr = INADDR_ANY;
	this->srv_address.sin_port = htons(port);
}

void SubServ::bindSubServ()
{
	if (bind(this->sock_desc, (struct sockaddr *)&this->srv_address,
		sizeof(this->srv_address)) < 0)
		throw SubServException("Error while binding socket");
}

void SubServ::socketListener()
{
	if (listen(this->sock_desc, 500) < 0)
		throw SubServException("Error while listening to socket");
}

void SubServ::printSubserv(void)
{
	std::cout << "SubServ" << " :" << std::endl ;
	std::cout << "  - SD	:" << getSocketDesc() << std::endl;
	std::cout << "  - client list : " << std::endl;
	printClientList();
}

void	SubServ::printClientList(void)
{
	for (std::list<Client *>::iterator i = getClientList().begin(); i != getClientList().end(); i++)
	{
		(*i)->printClient();
	}
}

void	SubServ::popClient(Client *client)
{
	this->client_list.remove(client);
	delete client;
}


///////////////////////////////////
///			  Getters			///
///////////////////////////////////

Server&	SubServ::getMainServer()
{
	return (this->main_serv);
}

int				SubServ::getSocketDesc()
{
	return(this->sock_desc);
}
		
sockaddr_in		SubServ::getAddress()
{
	return(this->srv_address);
}
		
Config::server	&SubServ::getConf()
{
	return(this->server_conf);
}

std::list<Client *> &SubServ::getClientList()
{
	return (this->client_list);
}

///////////////////////////////////
///			  Setters			///
///////////////////////////////////

void	SubServ::setClientList(Client *client)
{
	this->client_list.push_back(client);
}

///////////////////////////////////
///			Overloads			///
///////////////////////////////////


SubServ &SubServ::operator=(const SubServ& Other)
{
		this->main_serv = Other.main_serv;
		this->sock_desc = Other.sock_desc;
		this->option_buffer = Other.option_buffer;
		this->srv_address = Other.srv_address;
		this->server_conf = Other.server_conf;
		this->client_list = Other.client_list;
		return (*this);
}

