#ifndef USER_HPP
# define USER_HPP
# include <map>
# include <string>
# include <ctime>
# include "Message.hpp"
# include "Channel.hpp"

class User
{
	public:
		User(size_t id, std::string nickname, size_t hopcount, std::string ip);

//core
				
		void			sudo(bool state);//assigne la valeur state a admin
		Message 		send(std::string content, size_t dest_id, bool cmd);
		bool			connect(Channel channel, std::string pass = "");

//displays

		void			display();//display information
		void			display(User other);//display nickname && connected if admin show all
		void			display(Channel chan);//display name && mode si mode non privatif show users if admin show all
		void			display(Message message);//work if user concer by message or admin

//getters

		size_t			get_id();
		std::string 	get_nickname();
		std::string		get_real_name();
		size_t			get_hopcount();
		size_t			get_mode();
		Channel			get_channel();
		std::string		get_ip_address();
		time_t			get_time_at_logon();

//setters

		void			set_nickname(std::string new_nick);
		void			set_real_name(std::string new_name);
		void			set_mode(size_t mode);
		void			set_channel(Channel *channel);

		~User();
	private:
		size_t						id;
		std::string 				nickname;
		std::string					real_name;
		size_t						hopcount;
		size_t						mode;
		Channel						*channel;
		std::string					ip_address;

		time_t						time_at_logon;
};
#endif