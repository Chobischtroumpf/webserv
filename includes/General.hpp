#ifndef GENERAL_HPP
# define GENERAL_HPP

# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>

# include <cstring>
# include <cstdlib>
# include <ctime>
# include <iostream>
# include <string>
# include <vector>
# include <list>
# include <queue>
# include <stack>
# include <map>
# include <algorithm>
# include <iterator>
# include <iomanip>
# include <fstream>
# include <iostream>

# include "Exceptions.hpp"
# include "Config.hpp"

# define DEBUG(MSG) std::cout << "\033[0;35m\e[1m" << MSG << "\e[0m\033[0m" << std::endl;

# define BUFFER_SIZE 1000000

// Tools/utils.cpp:
	std::list<std::string> splitString(std::string str, std::string sep);
	std::string	ipBytesToIpv4(struct in_addr in);
	std::string& rtrim(std::string& s, const char* set);
	std::string& ltrim(std::string& s, const char* set);
	std::string& trim(std::string& s, const char* set);
	class Config;

// logger: pattern : void log_<what_you_are_logging>();
	void	logEnv();
	void	logFile(std::string file);
	void	logServConfig(Config::server config);

// checker: pattern : bool is_<what_you_are_checking>();
	bool	isIp(std::string ip);
	bool	isNumber(const std::string& s);


// Parsing/InitParser.cpp:
	void		parseEnv(char **env);
	std::string skipComment(std::string file);
	size_t		skipBrackets(std::string str);
	std::string	reverseStr(std::string str);
	size_t		skipWhitespaces(std::string str);
	size_t		countChar(char c, std::string str);
	int			contentType(std::string clientRequest);
	size_t		contentLength(std::string client_request);
	bool		isFile(const std::string& str);
	bool		file_exists(const std::string& str);
	bool		isDir(const std::string& str);
	void		ctrl_c(int signal);

#endif