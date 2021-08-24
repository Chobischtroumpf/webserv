#include "General.hpp"
#include "Client.hpp"
#include "Response.hpp"

///////////////////////////////////
///	Constructor and Destructors ///
///////////////////////////////////

Client::Client(int sd, std::string address)
{
	DEBUG("##### CLIENT INIT #####")
	this->socket = sd;
	setClientNonBlock();
	this->client_address = address;
	this->is_received = false;
}

Client::~Client(){
	DEBUG("Client destructor")
	}

///////////////////////////////////
///			  Methods			///
///////////////////////////////////

void Client::setClientNonBlock()
{
	if (fcntl(this->socket, F_SETFL, O_NONBLOCK) < 0)
		throw ("Error setting Client to nonblocking");
}

bool	Client::requestReceived()
{
	return (this->is_received);
}

int	Client::receiveRequest()
{
	size_t	pos;
	int read_ret;
	char buffer[BUFFER_SIZE + 1];

	bzero(buffer,BUFFER_SIZE + 1);
	if ((read_ret = read(socket, buffer, BUFFER_SIZE)) <= 0)
		return (-1);
	raw_request.append(buffer);
	int	type_content = contentType(raw_request);
	std::string end_body = type_content == 2 ? "0\r\n\r\n" : "\r\n\r\n";
	if ((pos = raw_request.find("\r\n\r\n")) != std::string::npos && type_content == 0)
		return (0);
	if (type_content > 0)
	{
		std::string body = raw_request.substr(pos + 4, raw_request.length() - (pos + 4));
		if (type_content == 1 && contentLength(raw_request) <= body.length())
			return (contentLength(raw_request) == body.length() ? 0 : -1);
		if ((pos = body.find(end_body)) != std::string::npos)
			if (((type_content == 2 && (pos == 0 || (body[pos - 1] == '\n' && body[pos - 2] == '\r')))
				|| type_content == 1))
				return (0);
	}
	return (1);
}

int	Client::sendRequest(Request &request)
{
	Response response(request);
	send(socket, response.getResponse().c_str(),response.getResponse().size(), 0);
	return (0);
}

void Client::printClient(void)
{	
	std::cout << std::left << "+-" << std::endl ;
	std::cout << std::left << "| Client" << " :" << std::endl ;
	std::cout << std::left << "|  - SD	: " << getSocketDesc() << std::endl;
	std::cout << std::left << "|  - Address: " << getAddress() << std::endl;
	std::cout << std::left << "|  - Request: " << getRequest() << std::endl;
	std::cout << std::left << "+-" << std::endl ;
}

///////////////////////////////////
///			  Getters			///
///////////////////////////////////

int		Client::getSocketDesc()
{
	return (this->socket);
}

std::string	Client::getRequest(void)
{
	return (this->raw_request);
}

std::string	Client::getAddress(void)
{
	return (this->client_address);
}

///////////////////////////////////
///			  Setters			///
///////////////////////////////////

void	Client::setReceived(bool received)
{
	this->is_received = received;
}

///////////////////////////////////
///			Overloads			///
///////////////////////////////////

Client &Client::operator=(const Client& Other)
{
		this->socket = Other.socket;
		this->client_address = Other.client_address;
		this->option_buffer = Other.option_buffer;
		this->request = Other.request;	
		return (*this);
}

bool operator==(const Client& lhs, const Client& rhs)
{
	if (lhs.socket == rhs.socket &&
			lhs.client_address == rhs.client_address &&
			lhs.option_buffer == rhs.option_buffer &&
			lhs.raw_request == rhs.raw_request)
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