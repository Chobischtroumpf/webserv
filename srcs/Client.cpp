#include "General.hpp"

Client::Client(int sd, std::string address)
{std::cout << "\033[0;35m\e[1mClient constructor\e[0m\033[0m" << std::endl;
	socket = sd;
	this->client_address = address;
}

int		Client::getSD()
{std::cout << "\033[0;35m\e[1mgetSD client\e[0m\033[0m" << std::endl;
	return (this->socket);
}

std::string	Client::getRequest(void)
{std::cout << "\033[0;35m\e[1mgetRequest\e[0m\033[0m" << std::endl;
	return (this->request);
}

void	Client::setReceived(bool received)
{std::cout << "\033[0;35m\e[1msetReceived\e[0m\033[0m" << std::endl;
	this->is_received = received;
}


bool	Client::requestReceived()
{std::cout << "\033[0;35m\e[1mrequestReceived\e[0m\033[0m" << std::endl;
	return (this->is_received);
}

// return -1 == error, 0 == On a fini de lire, 1 == Il reste des choses a lire
int	Client::receiveRequest()
{std::cout << "\033[0;35m\e[1mreceiveRequest\e[0m\033[0m" << std::endl;
	size_t	pos;
	int read_ret;
	char buffer[BUFFER_SIZE + 1];

	bzero(buffer,BUFFER_SIZE + 1);
	if ((read_ret = read(socket, buffer, BUFFER_SIZE)) <= 0)
		return (-1);
	request.append(buffer);
	std::clog << request << std::endl;
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

Client::~Client(){std::cout << "\033[0;35m\e[1mClient destructor\e[0m\033[0m" << std::endl;}
