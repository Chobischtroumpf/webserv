#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include <map>
# include <string>
# include <ctime>
# include <iostream>
# include "Message.hpp"
# include "User.hpp"


# define BAN_MASK				01000000000000000l
# define PASSW_SET_MODE			00100000000000000l
# define VERBOSE_MODE			00010000000000000l
# define MODERATED_MODE			00001000000000000l
# define PRIVATE_MODE			00000100000000000l
# define TOPIC_SETTABLE_MODE	00000010000000000l
# define INVITE_ONLY_MODE		00000001000000000l
# define SECRET_MODE			00000000100000000l
# define PRIVATE_MODE			00000000010000000l
# define OPERATOR_MODE			00000000000000001l


class Channel
{
	public:
		Channel(size_t id, std::string name, std::string mode, std::string pass = "");

//displays
		
		void					display();//display all information

//getters

		size_t					get_id();
		std::string				get_name();
		std::string				get_topic();
		std::string				get_pass();
		std::string				get_mode();
		size_t					get_user_limit();
		time_t					get_creation_time();
		std::map<size_t, User>	*get_connected_usrs();
		std::map<size_t, User>	*get_banned_usrs();

//setters

		void					set_topic(std::string topic);
		void					set_pass(std::string pass);
		void					set_mode(std::string mode);
		void					set_new_user(User new_user);

		~Channel();
	private:
		size_t					id;
		std::string				name;
		std::string				topic;
		std::string				pass;
		std::string				mode;
		size_t					user_limit;
		time_t					creation_time;
		std::map<size_t, User>	connected_usrs;
		std::map<size_t, User>	banned_usrs;

};

#endif