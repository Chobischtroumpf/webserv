#include "General.hpp"

extern std::map<std::string, std::string>	g_env;

void		parseEnv(char **env)
{
	for (size_t i = 0; env[i]; i++)
	{
		std::string temp = std::string(env[i]);
		g_env[temp.substr(0, temp.find("="))] = temp.substr(temp.find("=") + 1, temp.size());
	}
	// ft::logEnv();
}

// int readFile(std::string file, std::string *content)
// {
// 	char buff[BUFFER_SIZE + 1] = {0};
// 	int	fd;
// 	int	res;
// 	int i;

// 	fd = open(file.c_str(), O_RDONLY);
// 	if (fd == -1)
// 		return (-1);
// 	while ((res = read(fd, buff, BUFFER_SIZE)) > 0)
// 	{
// 		*content += buff;
// 		i = 0;
// 		while (i < res)
// 			buff[i++] = 0;
// 	}
// 	if (res < 0)
// 		return (-2); // request error_code -> 500
// 	close(fd);
// 	return (1);
// }

int readFile(std::string filename, std::string *content)
{
	std::ifstream file (filename, std::ifstream::binary);
	// file.open(filename, std::ios::in);
	if (!file.is_open())
		return (-2);
	content->assign((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	return (1);
}
