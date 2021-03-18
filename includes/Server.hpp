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
		Server(std::string pass = NULL);
		Message	check_request(std::queue<std::string> input);
		void	display_users(std::string mode = "all");//display users ['all' || 'connected' || 'disconnected']
		void	display_user(size_t id);
		void	display_chans();
		void	display_chan(size_t id);

		//setters

		void	add_user(User neo);//will check if user is in dsc_lst or usr_lst, if it is in neither, will create new user, if in dst_lst will swap to usr_lst
		void	add_channel(Channel neo);//will check if channel is in chan_lst, if it is not, will create new channel

		//getters
		
		User				*get_user(std::string nick);
		std::list<User>		*get_users();
		Channel				*get_chan(std::string);
		std::list<Channel>	*get_channels();
		~Server();

	private:
		std::string			pass; //can be set as we start the server, but is not mandatory, if set, before the creation of a User object, the server needs to get a PASS command with the correct password
		std::list<User>		usr_lst;
		std::list<User>		dsc_lst;//disconnected users list
		std::list<Channel>	chan_lst;
};

#endif