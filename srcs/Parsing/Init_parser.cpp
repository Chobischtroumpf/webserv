#include "../../includes/General.hpp"

std::list<std::string>		parse_optionnal_arg(std::string con_info)
{
	size_t 						first_sep = con_info.find(':');
	size_t 						second_sep = con_info.rfind(':');
	std::string					ip;
	std::string					port;
	std::string					password_network;
	std::list<std::string>		res;

	ip = con_info.substr(first_sep, second_sep - first_sep);
	port = con_info.substr(0, first_sep);
	password_network = con_info.substr(second_sep, con_info.size());
	if (is_ip(ip))
	{
		res.push_back(ip);
		res.push_back(port);
		res.push_back(password_network);
	}
	return (res);
}
