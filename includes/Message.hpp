#ifndef MESSAGE_HPP
# define MESSAGE_HPP
# include <string>
# include <iostream>

class Message
{
	public:
		Message(std::string content, size_t from, size_t to, bool command = false);	
		
//displays

		void		display();//display all information

//getters

		size_t		get_from();
		size_t		get_to();
		std::string	get_content();
		bool		get_command();

		~Message();
	private:
		size_t					from_id;
		size_t					to_id;
		std::string				content;
		bool					command;
};

#endif