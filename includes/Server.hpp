#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "General.hpp"

// #define USER_ID 0100000

// if id_t & USER_ID
// 	Userlst[id_t - USER_ID]
// class User;
// class Channel;
// class Message;

class Server
{
	public:

		fd_set			readfds;
		fd_set			writefds;
		
		std::set<int>	activeFileDes;

		Server();
		void	check_connections(); 
		Message	check_request(std::queue<std::string> input);
		Message	*check_time_out(std::map<size_t, User>);
		
//displays

		void	display_users(std::string mode = "all");//display users ['all' || 'connected' || 'disconnected']
		void	display_user(size_t id);
		void	display_chans();
		void	display_chan(size_t id);

//setters

		void	add_user(User neo);
		void	add_channel(Channel neo);//will check if channel is in chan_lst, if it is not, will create new channel

//unsetters

		void	delete_user(size_t id);
		void	delete_channel(size_t id);
		
//getters
		
		fd_set						get_readfds();
		int							get_sock_fd();
		sockaddr_in					get_addr();
		User						*get_user(size_t id);
		std::map<size_t, User>		*get_users();
		Channel						*get_chan(size_t id);
		std::map<size_t, Channel>	*get_channels();
		std::string					get_pass();
	
		~Server();

};

#endif