#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include <list>
# include <string>
# include <ctime>
# include "Message.hpp"
# include "User.hpp"

class Channel
{
	public:
		Channel(std::string name, size_t mode);
		void	display();//display all information
		~Channel();
	private:
		size_t			id;
		std::string		name;
		std::string		topic;
		std::string		pass;
		size_t			mode;
		time_t			creation_time;
		std::list<User>	connected_usr;	// same ici, pas plus simple de stocker le nick des users ? c'est plus opti en terme de memoire aussi non ?
};

#endif