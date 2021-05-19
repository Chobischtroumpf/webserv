#ifndef GENERAL_HPP
# define GENERAL_HPP 1

# include <sys/time.h>
# include <map>
# include <string>
# include <iostream>
# include <sstream>
# include <unistd.h>
# include <list>
# include <algorithm>
# include <cstdlib>
# include "WebServ.hpp"
# include "ParsingException.hpp"
# include "Config.hpp"
# define BUFFER_SIZE 256

// Tools/utils.cpp:
	std::list<std::string> split_string(std::string str, std::string sep);
	class Config;
// logger: pattern : void log_<what_you_are_logging>();
	void	log_env();
	void	log_file(std::string file);
	void	log_serv_config(Config::server config);

// checker: pattern : bool is_<what_you_are_checking>();
	bool	is_ip(std::string ip);
	bool	is_number(const std::string& s);

// Parsing/InitParser.cpp:
	void		parse_env(char **env);
	std::string skip_comment(std::string file);
	size_t	skip_brackets(std::string str);
	std::string	reverse_str(std::string str);
	size_t	skip_whitespaces(std::string str);
	size_t		count_char(char c, std::string str);
#endif