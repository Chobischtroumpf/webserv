#ifndef SERVER_HPP
# define SERVER_HPP
# include <list>
# include <queue>
# include "User.hpp"
# include "Channel.hpp"
# include "Message.hpp"


class Server
{
	public:
		Server();
		Message	check_request(std::queue<std::string> input);
		void	display_users(std::string mode = "all");//display users ['all' || 'connected' || 'disconnected']
		void	display_user(size_t id);
		void	display_chans();
		void	display_chan(size_t id);
		void	add_user(User neo);
		void	add_channel(Channel neo);
		~Server();
	private:
		std::list<User>		usr_lst;
		std::list<User>		dsc_lst;//disconnected users list	
		std::list<Channel>	chan_lst;
};

#endif