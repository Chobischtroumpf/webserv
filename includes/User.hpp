#ifndef USER_HPP
# define USER_HPP
# include <map>
# include <string>
# include <ctime>
# include <iostream>
# include "Server.hpp"
# include "Channel.hpp"
# include "Message.hpp"

# define INVISIBLE_MODE "i"
# define SERVER_NOTICE_MODE "s"
# define WALLOP_MODE "w"
# define OPERATOR_MODE "o"

class User
{
	public:
		User(size_t id, std::string nickname, size_t hopcount, std::string ip);

//core
				
		Message						send(std::string content, size_t dest_id, bool cmd);
		int							connect(Channel channel, std::string pass = "");

//displays

		void						display();//display information
		void						display(User other);//display nickname if admin show all
		void						display(Channel chan);//display name && mode si mode non privatif show users if admin show all
		void						display(Message message);//work if user concer by message or admin

//getters

		size_t						get_id();
		std::string					get_nickname();
		std::string					get_real_name();
		size_t						get_hopcount();
		size_t						get_mode();
		Channel						*get_channel(size_t chan_id);
		std::map<size_t, Channel>	*get_channels();
		std::string					get_ip_address();
		time_t						get_time_at_logon();

//setters

		void						set_nickname(std::string new_nick);
		void						set_real_name(std::string new_name);
		void						set_mode(std::string mode);
		void						set_channel(Channel *channel);

		~User();
	private:
		size_t						id;
		std::string 				nickname;
		std::string					real_name;
		size_t						hopcount;
		std::string					mode;
		std::map<size_t, Channel>	channel;
		std::string					ip_address;

		// time_t						time_at_logon;
};
#endif