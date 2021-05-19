#include "General.hpp"

extern std::map<std::string, std::string>	g_env;

//logger: pattern : void ft::log_<what_you_are_logging>();

void	log_env()
{
	for (std::map<std::string, std::string>::iterator i = g_env.begin(); i != g_env.end(); i++)
		std::clog << "\033[0;34m[" << i->first << "]\033[0m = \033[0;32m[" << i->second << "]\033[0m" << std::endl;
}

void	log_file(std::string file)
{
	std::clog << file << std::endl;
}

void	log_serv_config(Config::server config)
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
}

//Checker:  pattern : bool ft::is_<what_you_are_checking>();

bool	is_ip(std::string ip)
{
	return (inet_addr(ip.c_str()) != (in_addr_t)(-1));
}

std::string skip_comment(std::string file)
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

std::string	reverse_str(std::string str)
{
	int n = str.length();

	for (int i = 0; i < n / 2; i++)
		std::swap(str[i], str[n - i - 1]);
	return (str);
}

size_t	count_char(char c, std::string str)
{
	size_t count = 0;

	for (std::string::iterator i = str.begin(); i != str.end(); i++)
		if (*i == c)
			count++;
	return (count);
}

//sep has to be one char long
std::list<std::string> split_string(std::string str, std::string sep)
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

size_t	skip_whitespaces(std::string str)
{
	int i = -1;
	while (str[++i])
		if (!isspace(str[i]))
			break;
	return (i);
}

size_t	skip_brackets(std::string str)
{
	int i = -1;
	while (str[i] == '[' || str[i] == ']' || str[i] =='{' || str[i] == '}' || str[i] == '(' || str[i] == ')')
		i++;
	return (i);
}

bool is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it++));
	return !s.empty() && it == s.end();
}
