#ifndef USER_HPP
# define USER_HPP
# include <list>
# include <string>
# include "Message.hpp"


class User
{
	public:
		User(std::string nickname, std::string pass, size_t hopcount, std::string ip);
		void	sudo(bool state);//assigne la valeur state a admin
		Message send(std::string content, size_t dest_id, bool cmd);
		void	connect(std::string nickname, std::string pass);
		bool	connect(size_t channel_id, std::string pass = "");
		void	disconnect();
		void	display();//display information
		void	display(User other);//display nickname && connected if admin show all
		void	display(Channel chan);//display name && mode si mode non privatif show users if admin show all
		void	display(Message message);//work if user concer by message or admin
		~User();
	private:
		size_t				id;
		std::string 		nickname;
		std::string 		pass;
		bool				admin = false;
		size_t				hopcount;
		std::list<size_t>	channel_id;
		std::string			ip_address;
		bool				connected;
};

#endif