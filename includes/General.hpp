#ifndef GENERAL_HPP
# define GENERAL_HPP
# include "Server.hpp"

// Tools/utils.cpp:

bool	is_ip(std::string ip);

// Parsing/InitParser.cpp:

std::list<std::string>		parse_optionnal_arg(std::string con_info);

#endif