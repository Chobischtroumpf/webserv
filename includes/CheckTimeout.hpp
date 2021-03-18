#ifndef CHECKTIMEOUT_HPP
# define CHECKTIMEOUT_HPP

# include "Server.hpp"

class CheckTimeout
{
	public:
		CheckTimeout(std::map<size_t, User> *lst_usrs);
	private:
		std::map<size_t, User>	*lst_usrs;
		const Message			timeout_msg;
};

#endif