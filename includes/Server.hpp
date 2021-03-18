#ifndef SERVER_HPP
# define SERVER_HPP
# include <map>
# include <queue>
# include "User.hpp"
# include "Channel.hpp"
# include "Message.hpp"

// #define USER_ID 0100000

// if id_t & USER_ID
// 	Userlst[id_t - USER_ID]

class Server
{
	public:
		Server(std::string pass = NULL);
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
		
		User						*get_user(std::string nick);
		std::map<size_t, User>		*get_users();
		Channel						*get_chan(std::string);
		std::map<size_t, Channel>	*get_channels();
		std::string					get_pass();
	
		~Server();

	private:
		std::string					pass; //can be set as we start the server, but is not mandatory, if set, before the creation of a User object, the server needs to get a PASS command with the correct password
		std::map<size_t, User>		usr_lst;
		std::map<size_t, Channel>	chan_lst;
};

#endif