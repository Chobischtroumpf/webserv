#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include <map>
# include <string>
# include <ctime>
# include <iostream>
# include "Message.hpp"
# include "User.hpp"

class Channel
{
	public:
		Channel(size_t id, std::string name, size_t mode, std::string pass = "");

//displays
		
		void					display();//display all information

//getters

		size_t					get_id();
		std::string				get_name();
		std::string				get_topic();
		std::string				get_pass();
		size_t					get_mode();
		time_t					get_creation_time();
		std::map<size_t, User>	get_connected_usrs();

//setters

		void					set_topic(std::string topic);
		void					set_pass(std::string pass);
		void					set_mode(size_t mode);
		void					set_new_user(User new_user);

		~Channel();
	private:
		size_t					id;
		std::string				name;
		std::string				topic;
		std::string				pass;
		size_t					mode;
		time_t					creation_time;
		std::map<size_t, User>	connected_usrs;
};

#endif