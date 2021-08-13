#include "SubServ.hpp"

void SubServ::createSD()
{
	//DEBUG("createSD")
	if ((this->sock_desc = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		throw SubServException("Creation of the SubServ descriptor failed");
}


void SubServ::setSockOption()
{
	//DEBUG("setSockOption")
	if (setsockopt(this->sock_desc, SOL_SOCKET, SO_REUSEADDR,
		&this->option_buffer, sizeof(this->option_buffer)))
		throw SubServException("setting socket options failed");
}

void SubServ::setSubServNonBlock()
{
	//DEBUG("setSubServNonBlock")
	if (fcntl(this->sock_desc, F_SETFL, O_NONBLOCK) < 0)
		throw SubServException("Error setting SubServ to nonblocking");
}

void SubServ::initAddress(int port)
{
	//DEBUG("initAddress")
	this->srv_address.sin_family = AF_INET;
	this->srv_address.sin_addr.s_addr = INADDR_ANY;
	this->srv_address.sin_port = htons(port);
}

void SubServ::bindSubServ()
{
	//DEBUG("bindSubServ")
	if (bind(this->sock_desc, (struct sockaddr *)&this->srv_address,
		sizeof(this->srv_address)) < 0)
		throw SubServException("Error while binding socket");
}

void SubServ::socketListener()
{
	//DEBUG("socketListener")
	if (listen(this->sock_desc, 500) < 0)
		throw SubServException("Error while listening to socket");
}

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

void SubServ::printSubserv(void)
{
	std::cout << "SubServ" << " :" << std::endl ;
	std::cout << "  - SD	:" << getSocketDesc() << std::endl;
	std::cout << "  - client list : " << std::endl;
	printClientList();
}

int				SubServ::getSocketDesc()
{
	//DEBUG("getSocketDesc")
	return(this->sock_desc);
}
		
sockaddr_in		SubServ::getAddress()
{
	//DEBUG("getAddress")
	return(this->srv_address);
}
		
Config::server	SubServ::getConf()
{
	//DEBUG("getConf")
	return(this->server_conf);
}

std::list<Client> &SubServ::getClientList()
{
	//DEBUG("getClientList")
	return (this->client_list);
}

void	SubServ::setClientList(const Client &client)
{
	//DEBUG("setClientList")
	this->client_list.push_back(client);
}

void	SubServ::printClientList(void)
{
	for (std::list<Client>::iterator i = getClientList().begin(); i != getClientList().end(); i++)
	{
		(*i).printClient();
	}
}

void	SubServ::popClient(const Client &client)
{DEBUG("popClient")
	this->client_list.remove(client);
}

Server	SubServ::getMainServer()
{
	//DEBUG("getMainServer")
	return (this->main_serv);
}

SubServ &SubServ::operator=(const SubServ& Other)
{
	//DEBUG("Subserv =")
		this->main_serv = Other.main_serv;
		this->sock_desc = Other.sock_desc;
		this->option_buffer = Other.option_buffer;
		this->srv_address = Other.srv_address;
		this->server_conf = Other.server_conf;
		this->client_list = Other.client_list;
		return (*this);
}

SubServ::~SubServ(){
	//DEBUG("socket destructor")
	}
		