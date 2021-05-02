#ifndef GENERAL_HPP
# define GENERAL_HPP 1

# include "WebServ.hpp"
# include "ParsingException.hpp"
# include "Config.hpp"
# include <sys/time.h>
# include <map>
# include <string>
# include <iostream>
# include <sstream>
# include <unistd.h>
# include <list>
# define BUFFER_SIZE 256

// Tools/utils.cpp:

// logger: pattern : void log_<what_you_are_logging>();
	void	log_env();
	void	log_file(std::string file);

// checker: pattern : bool is_<what_you_are_checking>();
	bool	is_ip(std::string ip);

// Parsing/InitParser.cpp:
	void		parse_env(char **env);
	std::string skip_comment(std::string file);
	std::string	reverse_str(std::string str);
#endif