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

# include "Exceptions.hpp"
# include "Config.hpp"
// # include "Socket.hpp"
# include "Server.hpp"

# define DEBUG(MSG) std::cout << "\033[0;35m\e[1m" MSG "\e[0m\033[0m" << std::endl;

# define BUFFER_SIZE 1000000

// Tools/utils.cpp:
	std::list<std::string> splitString(std::string str, std::string sep);
	std::string ipBytesToIpv4(struct in_addr in);
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

#endif
