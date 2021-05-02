#include "General.hpp"

extern std::map<std::string, std::string>	g_env;

void		parse_env(char **env)
{
	for (size_t i = 0; env[i]; i++)
	{
		std::string temp = std::string(env[i]);
		g_env[temp.substr(0, temp.find("="))] = temp.substr(temp.find("=") + 1, temp.size());
	}
	// ft::log_env();
}

std::string readFile(std::string file)
{
	char buff[BUFFER_SIZE + 1] = {0};
	int	fd;
	int	res;
	int i;
	std::string result;

	fd = open(file.c_str(), O_RDONLY);
	if (fd == -1)
		throw ParsingException(0, "the file " + file + " does not exist.");
	while ((res = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		result += buff;
		i = 0;
		while (i < BUFFER_SIZE)
			buff[i++] = 0;
	}
	if (res < 0)
		throw ParsingException(0, "Error while Reading " + file + ".");
	close(fd);
	return (result);
}