#ifndef USER_HPP
# define USER_HPP
# include <list>
# include <string>
# include <ctime>
# include "Message.hpp"
# include "Channel.hpp"


class User
{
	public:
		User(std::string nickname, size_t hopcount, std::string ip);
		void	sudo(bool state);//assigne la valeur state a admin
		Message send(std::string content, size_t dest_id, bool cmd);
		void	connect(std::string nickname);
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
		std::string			real_name;
		size_t				hopcount;
		size_t				mode;
		std::list<Channel>	channel;
		std::string			ip_address;
		time_t				time_at_logon;
		bool				connected;
};
// enlever le PASS ici, car j'avais mal compris a quoi servait la commande pass, je l'ai deplacer dans la class server
#endif