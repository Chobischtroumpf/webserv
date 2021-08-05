#include "General.hpp"

Client::Client(int sd, std::string address)
{
	DEBUG("##### CLIENT INIT #####")
	socket = sd;
	this->client_address = address;
}

int		Client::getSocketDesc()
{
	//DEBUG("getSocketDesc client")
	return (this->socket);
}

std::string	Client::getRequest(void)
{
	//DEBUG("getRequest")
	return (this->request);
}

std::string	Client::getAddress(void)
{
	return (this->client_address);
}

void	Client::setReceived(bool received)
{
	//DEBUG("setReceived")
	this->is_received = received;
}


bool	Client::requestReceived()
{
	//DEBUG("requestReceived")
	return (this->is_received);
}

// return -1 == error, 0 == On a fini de lire, 1 == Il reste des choses a lire
int	Client::receiveRequest()
{
	DEBUG("receiveRequest")
	size_t	pos;
	int read_ret;
	char buffer[BUFFER_SIZE + 1];

	bzero(buffer,BUFFER_SIZE + 1);
	if ((read_ret = read(socket, buffer, BUFFER_SIZE)) <= 0)
		return (-1);
	request.append(buffer);
	int	type_content = contentType(request);
	std::string end_body = type_content == 2 ? "0\r\n\r\n" : "\r\n\r\n";
	//check si on a tout le header
	if ((pos = request.find("\r\n\r\n")) != std::string::npos && type_content == 0)
		return (0);
	if (type_content > 0)
	{
		std::string body = request.substr(pos + 4, request.length() - (pos + 4));
		if (type_content == 1 && contentLength(request) <= body.length())
			return (contentLength(request) == body.length() ? 0 : -1);
		if ((pos = body.find(end_body)) != std::string::npos)
			if (((type_content == 2 && (pos == 0 || (body[pos - 1] == '\n' && body[pos - 2] == '\r')))
				|| type_content == 1))
				return (0);
	}
	return (1);
}

Client &Client::operator=(const Client& Other)
{
		this->socket = Other.socket;
		this->client_address = Other.client_address;
		this->option_buffer = Other.option_buffer;
		this->request = Other.request;	
		return (*this);
}

// bool &Client::operator==(const Client& lhs, const Client& rhs)
// {
// 	if (lhs.socket == rhs.socket)
// 		return true;
// 	return false;
// }

void Client::printClient(void)
{	
	
	std::cout << std::left << "+-" << std::endl ;
	std::cout << std::left << "| Client" << " :" << std::endl ;
	std::cout << std::left << "|  - SD	: " << getSocketDesc() << std::endl;
	std::cout << std::left << "|  - Address: " << getAddress() << std::endl;
	std::cout << std::left << "|  - Request: " << getRequest() << std::endl;
	std::cout << std::left << "+-" << std::endl ;
}

bool operator==(const Client& lhs, const Client& rhs)
{
	if (lhs.socket == rhs.socket &&
			lhs.client_address == rhs.client_address &&
			lhs.option_buffer == rhs.option_buffer &&
			lhs.request == rhs.request)
		return (true);
	return (false);
}

std::ostream &operator<<(std::ostream &os, Client &other)
{
	os << "Client" << " :" << std::endl 
	<< "  - SD	:" << other.getSocketDesc() << std::endl
	<< "  - Address: " << other.getAddress() << std::endl
	<< "  - Request: " << other.getRequest() << std::endl;
	return (os);
}


Client::~Client(){DEBUG("Client destructor")}
