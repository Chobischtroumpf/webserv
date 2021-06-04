#ifndef GENERAL_HPP
# define GENERAL_HPP

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <time.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# include <iostream>
# include <string>
# include <vector>
# include <list>
# include <queue>
# include <stack>
# include <map>
# include <algorithm>
# include <iterator>

# include "Exceptions.hpp"
# include "Config.hpp"
// # include "Socket.hpp"
# include "Server.hpp"


# define BUFFER_SIZE 256

// Tools/utils.cpp:
	std::list<std::string> split_string(std::string str, std::string sep);
	std::string ipbytes_to_ipv4(struct in_addr in);
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
