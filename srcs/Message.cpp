#include "Message.hpp"

Message::Message(std::string content, size_t from, size_t to, bool command = false)
{
	this->content = content;
	this->from_id = from;
	this->to_id = to;
	this->command = command;
}

void		Message::display()
{
	std::cout << "_____MESSAGE_____" << std::endl;
	std::cout << "[FROM] : " << this->from_id << std::endl;
	std::cout << "[TO] : " << this->to_id << std::endl;
	std::cout << "[COMMAND] : " << this->command << std::endl;
	std::cout << "[CONTENT] : " << this->content << std::endl;	
}

size_t		Message::get_from()
{
	return(this->from_id);
}

size_t		Message::get_to()
{
	return(this->to_id);
}

std::string	Message::get_content()
{
	return(this->content);
}

bool		Message::get_command()
{
	return(this->command);
}

Message::~Message(){}