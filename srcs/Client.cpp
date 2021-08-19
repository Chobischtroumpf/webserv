#include "General.hpp"
#include "Client.hpp"
#include "Response.hpp"

Client::Client(int sd, std::string address)
{
	DEBUG("##### CLIENT INIT #####")
	this->socket = sd;
	setClientNonBlock();
	this->client_address = address;
	this->is_received = false;
}

void Client::setClientNonBlock()
{
	//DEBUG("setClientNonBlock")
	if (fcntl(this->socket, F_SETFL, O_NONBLOCK) < 0)
		throw ("Error setting Client to nonblocking");
}

int		Client::getSocketDesc()
{
	//DEBUG("getSocketDesc client")
	return (this->socket);
}

std::string	Client::getRequest(void)
{
	//DEBUG("getRequest")
	return (this->raw_request);
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
	//DEBUG("receiveRequest")
	size_t	pos;
	int read_ret;
	char buffer[BUFFER_SIZE + 1];

	bzero(buffer,BUFFER_SIZE + 1);
	if ((read_ret = read(socket, buffer, BUFFER_SIZE)) <= 0)
		return (-1);
	raw_request.append(buffer);
	int	type_content = contentType(raw_request);
	std::string end_body = type_content == 2 ? "0\r\n\r\n" : "\r\n\r\n";
	//check si on a tout le header
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

int	Client::sendRequest(Request request)
{
	Response res(request);
	std::cout << "__________________________" << std::endl;
	std::cout << res.getResponse() << std::endl;
	std::cout << "__________________________" << std::endl;

	//send(this->socket, "HTTP/1.1 200 OK\nContent-Type: text/html\n\r\n\rOUI", 47,0);
	send(this->socket, (res.getResponse()).c_str(), res.getResponse().size(),0);
	// create Response object with HttpRequest
	// once created, get response string
	// write response string into client's socket
	// if write = -1 client disconnected, call pop client
	// set is_received to false
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


Client::~Client(){
	//DEBUG("Client destructor")
	}
