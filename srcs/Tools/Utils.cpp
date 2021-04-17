#include "General.hpp"

bool	is_ip(std::string ip)
{
	return (inet_addr(ip.c_str()) != (in_addr_t)(-1));
}