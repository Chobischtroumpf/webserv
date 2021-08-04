#include "General.hpp"

std::map<std::string, std::string>	g_env;

int	main(int ac, char **av, char **env)
{
	DEBUG("THIS IS A TEST")
	if (ac != 2)
	{
		std::clog << "[Webserv error] :" << std::endl << "	usage: ./webserv [path]" << std::endl;
		return (1);
	}
	try
	{
		parseEnv(env);
		// logEnv();
		Config config(av[1]);
		Server serv(config);
		serv.listenIt();
	}
	catch(const std::exception& e)
	{
		throwError(e);
	}

	return (0);
}
