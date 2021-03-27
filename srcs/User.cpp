#include "User.hpp"

User::User(size_t id, std::string nickname, size_t hopcount, std::string ip):
	id(id), nickname(nickname), hopcount(hopcount), ip_address(ip)
{
}

Message	User::send(std::string content, size_t dest_id, bool cmd)
{
	Message	message(content, this->id, dest_id, cmd);
}

int	User::connect(Channel channel, std::string pass = "")
{
	std::map<size_t, User>	*users_connected = channel.get_connected_usrs();
	std::map<size_t, User>	*users_banned = channel.get_banned_usrs();
	if(pass == channel.get_pass())
	{
		this->channel[channel.get_id()] = channel;
		channel.set_new_user(*this);
		//renvoyer RPL_TOPIC au client via le socket
	}
	else
		//renvoyer ERR_BADCHANNELKEY au client via le socket

}

void	User::display()
{
	//faudra remplacer cout par le fd du socket
	std::cout << "Nick: " << this->nickname << " Real Name: " << this->real_name
		<< " hopcount: " << this->hopcount << " Ip Address: " << this->ip_address
		<< "mode: " << this->mode << std::endl;
}

//getters

size_t		User::get_id()
{
	return (this->id);
}

std::string					User::get_nickname()
{
	return (this->nickname);
}

std::string					User::get_real_name()
{
	return (this->real_name);
}

size_t						User::get_hopcount()
{
	return (this->hopcount);
}

size_t						User::get_mode()
{
	return (this->mode);
}

Channel						*User::get_channel(size_t chan_id)
{
	return (&this->channel[chan_id]);
}
std::map<size_t, Channel>	*User::get_channels()
{
	return (&this->channel);
}

std::string					User::get_ip_address()
{
	return (this->ip_address);
}

time_t						User::get_time_at_logon()
{
	return (this->get_time_at_logon());
}

//setters

void	User::set_nickname(std::string new_nick)
{
	this->nickname = new_nick;
}

void	User::set_real_name(std::string new_name)
{
	this->real_name = new_name;
}

void    User::set_mode(std::string mode)
{
	bool	remove = true;
	size_t	position;
	int		i = 0;

	if (mode[i] == '+')
		remove = false;
	while (mode[++i])
		if (((position = this->mode.find(mode[i])) != std::string::npos) && remove)
			this->mode.erase(this->mode.begin() + position);
		else
			if (!remove && position == std::string::npos)
				this->mode += mode[i];
}

void	User::set_channel(Channel *channel)
{
	this->channel[channel->get_id()] = *channel;
}

User::~User(){}