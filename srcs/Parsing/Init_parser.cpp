#include "General.hpp"

extern std::map<std::string, std::string>	g_env;

void		parseEnv(char **env)
{
	for (size_t i = 0; env[i]; i++)
	{
		std::string temp = std::string(env[i]);
		g_env[temp.substr(0, temp.find("="))] = temp.substr(temp.find("=") + 1, temp.size());
	}
}

int readFile(std::string filename, std::string *content)
{
	std::ifstream file (filename, std::ifstream::binary);
	if (!file.is_open())
		return (-1);
	content->assign((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	return (1);
}
