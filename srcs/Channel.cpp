#include "../includes/Channel.hpp"

Channel::Channel(size_t id, std::string name, size_t mode, std::string pass = "")
{
	this->id = id;
	this->name = name;
	this->mode = mode;
	this->pass = pass;
}

void					Channel::display()
{
	std::cout << "_____CHANNEL_" << this->id << "_____" << std::endl;
	std::cout << "[NAME] : " << this->name << std::endl;
	std::cout << "[PASS] : " << this->pass << std::endl;
	std::cout << "[MODE] : " << this->mode << std::endl;
	//ADD CREATION TIME
	//ADD USERS LIST
}

size_t					Channel::get_id()
{
	return (this->id);
}

std::string				Channel::get_name()
{
	return (this->name);
}

std::string				Channel::get_topic()
{
	return (this->topic);
}

std::string				Channel::get_pass()
{
	return (this->pass);
}

size_t					Channel::get_mode()
{
	return (this->mode);
}

time_t					Channel::get_creation_time()
{
	return (this->creation_time);
}

std::map<size_t, User>	Channel::get_connected_usrs()
{
	return (this->connected_usrs);
}

void					Channel::set_topic(std::string topic)
{
	this->topic = topic;
}

void					Channel::set_pass(std::string pass)
{
	this->pass = pass;
}

void					Channel::set_mode(size_t mode)
{
	this->mode = mode;
}

void					Channel::set_new_user(User new_user)
{
	this->connected_usrs[new_user.get_id()] = new_user;
}

Channel::~Channel(){}