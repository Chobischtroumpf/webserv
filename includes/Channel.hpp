#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include <list>
# include <string>
# include "Message.hpp"

class Channel
{
	public:
		Channel(std::string name, size_t mode);
		void	display();//display all information
		~Channel();
	private:
		size_t				id;
		std::string			name;
		std::string			pass;
		size_t				mode;
		std::list<size_t>	connected_usr;
};

#endif