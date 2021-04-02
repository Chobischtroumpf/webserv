#include "Server.hpp"

int	main(int ac, char **av)
{
	//./ircserv [host:port_network:password_network] <port> <password>
	// parser la ligne ci dessus proprement pour lancer le serveur dans
	// tous les cas ou renvoyer une erreur.
	int i;

	if (!is_ip(av[1]))
		i = 1;
	else
		i = 2;
	//adapte le constructeur au besoin du pdf
	Server serv(atoi(av[i]), av[i+1]); //hardcodé car on s'occupera plus tard des connection inter serveur
	while(true)
	{
		serv.listen(); // s'occupe de detecter si un nouveau user est arriver, ou pas.
		serv.check_requests(); // s'occupe de controller si un user a envoyer un message que le serveur doit gerer
		serv.check_time_out(); // vas ping les user pour controller que la connection n'a pas ete perdue, dans le cas ou le user est deconnecter, ca envoie le message QUIT au serveur
	}
	return (0);
}