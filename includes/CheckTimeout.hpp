#ifndef CHECKTIMEOUT_HPP
# define CHECKTIMEOUT_HPP

# include "Server.hpp"

class CheckTimeout
{
	public:
	CheckTimeout(Server server);
	private:
	Server	server;
	Message	timeout_msg;
};

#endif