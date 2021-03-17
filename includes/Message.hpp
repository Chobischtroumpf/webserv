#ifndef MESSAGE_HPP
# define MESSAGE_HPP
# include <list>
# include <string>

class Message
{
	public:
		Message(std::string content, size_t from, size_t to, bool command = false);
		void	display();//display all information
		~Message();
	private:
		size_t				id;
		size_t				user_id;	//ce serait pas plus simple de stocker le nick ?
		size_t				channel_id;
		size_t				target_id;
		std::string			content;
		bool				command;
};

#endif