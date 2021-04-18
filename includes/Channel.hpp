#ifndef CHANNEL_HPP
# define CHANNEL_HPP
# include <map>
# include <string>
# include <ctime>
# include <iostream>
# include "Message.hpp"
# include "User.hpp"

# define USER_LIMIT				"l"
# define BAN_MASK				"b"
# define PASSW_SET_MODE			"k"
# define VERBOSE_MODE			"v"
# define MODERATED_MODE			"m"
# define LOCAL_MODE				"n"
# define TOPIC_SETTABLE_MODE	"t"
# define INVITE_ONLY_MODE		"i"
# define SECRET_MODE			"s"
# define PRIVATE_MODE			"p"
# ifndef OPERATOR_MODE
#  define OPERATOR_MODE			"o"
# endif

class User;

class Channel
{
	public:
		Channel(){};
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