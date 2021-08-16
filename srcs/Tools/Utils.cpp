# include "General.hpp"
# include "Request.hpp"
extern std::map<std::string, std::string>	g_env;

//logger: pattern : void ft::log_<what_you_are_logging>();

void	logEnv()
{
	for (std::map<std::string, std::string>::iterator i = g_env.begin(); i != g_env.end(); i++)
		std::clog << "\033[0;34m[" << i->first << "]\033[0m = \033[0;32m[" << i->second << "]\033[0m" << std::endl;
}

void	logFile(std::string file)
{
	std::clog << file << std::endl;
}

void	logServConfig(Config::server config)
{
	std::clog << "\033[0;34m[server_names]\033[0m = \033[0;32m[";
	for (std::list<std::string>::iterator it = config.names.begin(); it != config.names.end(); it++)
		std::clog << *it + ", ";
	std::clog << "]\033[0m" << std::endl;
	std::clog << "\033[0;34m[server_host]\033[0m = \033[0;32m[" << config.host << "]\033[0m" << std::endl;
	std::clog << "\033[0;34m[server_root]\033[0m = \033[0;32m[" << config.root << "]\033[0m" << std::endl;
	for (std::map<int, std::string>::iterator it = config.error_pages.begin(); it != config.error_pages.end(); it++)
		std::clog << "\033[0;34m[" << it->first << "]\033[0m = \033[0;32m[" << it->second << "]\033[0m" << std::endl;
	std::clog << "\033[0;34m[server_port]\033[0m = \033[0;32m[" << config.port << "]\033[0m" << std::endl;
	std::clog << "\033[0;34m[Locations]\033[0m = \033[0;32m" << std::endl << "{" << std::endl;
	std::clog << "}\033[0m" << std::endl;
}

bool	isIp(std::string ip)
{
	return (inet_addr(ip.c_str()) != (in_addr_t)(-1));
}

std::string skipComment(std::string file)
{
	size_t	pos_hash;
	size_t	pos_nl;
	
	while((pos_hash = file.find("#")) != std::string::npos)
	{
		pos_nl = file.find("\n", pos_hash);
		file.replace(pos_hash,  pos_nl - pos_hash,  "");
	}
	return (file);
}

std::string uIntegerToString(size_t n)
{
	std::ostringstream convert;

	convert << n;
	return (convert.str());
}

void throwError(const std::exception& ex)
{
	std::cerr << "\033[1m\033[31mERROR \033[0m: " << ex.what() << '\n';
}

std::string	reverseStr(std::string str)
{
	int n = str.length();

	for (int i = 0; i < n / 2; i++)
		std::swap(str[i], str[n - i - 1]);
	return (str);
}

std::string& rtrim(std::string& s, const char* set)
{
    s.erase(s.find_last_not_of(set) + 1);
    return s;
}

std::string& ltrim(std::string& s, const char* set)
{
    s.erase(0, s.find_first_not_of(set));
    return s;
}

std::string& trim(std::string& s, const char* set)
{
    return ltrim(rtrim(s, set), set);
}

size_t	countChar(char c, std::string str)
{
	size_t count = 0;

	for (std::string::iterator i = str.begin(); i != str.end(); i++)
		if (*i == c)
			count++;
	return (count);
}

std::list<std::string> splitString(std::string str, std::string sep)
{
	std::list<std::string> ret;
	size_t start = 0;
	size_t end = 0;
	while((end = str.find(sep, start)) != std::string::npos)
	{
		if (end - start != 0)
			ret.push_back(str.substr(start, end - start));
		start = end + 1;
	}
	if (end - start != 0)
			ret.push_back(str.substr(start, end - start));
	return ret;
}

size_t	skipWhitespaces(std::string str)
{
	int i = -1;
	while (str[++i])
		if (!isspace(str[i]))
			break;
	return (i);
}

size_t	skipBrackets(std::string str)
{
	int i = 0;
	while (str[i] == '[' || str[i] == ']' || str[i] =='{' || str[i] == '}' || str[i] == '(' || str[i] == ')')
		i++;
	return (i);
}

bool isNumber(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it++));
	return (!s.empty() && it == s.end());
}

std::string	ipBytesToIpv4(struct in_addr in)
{
	std::stringstream buffer;

	unsigned char *bytes = (unsigned char *) &in;
	for (int cur_bytes = 0; cur_bytes < 4; cur_bytes++)
		buffer << (int)bytes[cur_bytes] << '.';
	std::string str = buffer.str();
	return (str.substr(0, str.length() - 1));
}

// return 0 == rien, 1 == Content-Length defined, 2 == chunked (reception du message par paquet)
int	contentType(std::string client_request)
{
	//DEBUG("contentType")
	size_t pos = 0;
	size_t pos_in_line = 0;
	std::string line;

	for (size_t end = client_request.find("\n"); end != std::string::npos; end = client_request.find("\n", pos))
	{
		line = client_request.substr(pos, end - pos);
		if ((pos_in_line = line.find("Transfer-Encoding: chunked")) != std::string::npos && pos_in_line == 0)
			return (2);
		else if ((pos_in_line = line.find("Content-Length")) != std::string::npos && pos_in_line == 0)
			return (1);
		if ((pos_in_line = client_request.find("\r\n\r\n")) != std::string::npos && pos_in_line == pos)
			break;
		pos = end + 1;
	}
	return (0);
}

size_t contentLength(std::string client_request)
{
	size_t pos = 0;
	size_t pos_in_line = 0;
	std::string line;

	for (size_t end = client_request.find("\n"); end != std::string::npos; end = client_request.find("\n", pos))
	{
		line = client_request.substr(pos, end - pos);
		if ((pos_in_line = line.find("Content-Length")) != std::string::npos && pos_in_line == 0)
			return (atoi(line.substr(line.find(":") + 2, line.length()).c_str()));
		if ((pos_in_line = client_request.find("\r\n\r\n")) != std::string::npos && pos_in_line == pos)
			break;
		pos = end + 1;
	}
	return (0);
}



Config::location	&getLocationConfig(Config::server server_config, HttpRequest request)
{
	return (server_config.locations[request.GetPath()]);
}

// -1 : stat failed or nor a file or directory
// 0  : is a directory
// 1  : is a file

int		isFile(std::string path)
{
	struct stat info;
	if (stat(path.c_str(), &info) != 0)
		return (-1);
	else
	{
		if (S_ISREG(info.st_mode))
			return (1);
		else if (S_ISDIR(info.st_mode))
			return (0);
		else
			return (-1);
	}
}