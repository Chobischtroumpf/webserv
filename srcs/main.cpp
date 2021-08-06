#include "General.hpp"

std::map<std::string, std::string>	g_env;

Server *server;

void	ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		for (std::list<SubServ>::iterator subserver = server->sub_serv.begin(); subserver != server->sub_serv.end(); subserver++)
		{
			for (std::list<Client>::iterator client = (*subserver).getClientList().begin(); client != (*subserver).getClientList().end(); client++)
				close((*client).getSD());
			close((*subserver).getSD());
		}
		server->keep_going = false;
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac != 2)
	{
		std::clog << "[Webserv error] :" << std::endl << "	usage: ./webserv [path]" << std::endl;
		return (1);
	}
	signal(SIGINT, ctrl_c);
	try
	{
		parseEnv(env);
		// logEnv();
		Config config(av[1]);
		Server serv(config);
		server = &serv;
		serv.listenIt();
	}
	catch(const std::exception& e)
	{
		throwError(e);
	}

	return (0);
}
