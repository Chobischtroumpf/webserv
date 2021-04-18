#include "General.hpp"

int	init_listen(Server serv)
{//init
	fd_set	tmp_readfds = serv.get_readfds();
	std::map<size_t, User> *usr_lst = serv.get_users();
	int	max_sd = serv.get_sock_fd();

	//clear the socket set
	FD_ZERO(&tmp_readfds);
	//add master socket to set
	FD_SET(serv.get_sock_fd(), &tmp_readfds);
	//add child sockets to set
	for (std::map<size_t, User>::iterator user = (*usr_lst).begin(); user != (*usr_lst).end(); user++)
	{
		if (user->second.get_sock_fd_id() > 0)
			FD_SET(user->second.get_sock_fd_id(), &tmp_readfds);
		if (user->second.get_sock_fd_id() > max_sd)
			max_sd = user->second.get_sock_fd_id();
	}
	return (select(max_sd + 1, &tmp_readfds, NULL, NULL, NULL));
}//return : select return

int	incoming_connection(Server serv)
{
	int	new_sock;
	fd_set	tmp_readfds = serv.get_readfds();
	int	addrlen = sizeof(serv.get_addr());

	if (FD_ISSET(serv.get_sock_fd(), &tmp_readfds))
	{
		std::string ip;
		struct sockaddr_in client_addr = serv.get_addr();
		if ((new_sock = accept(serv.get_sock_fd(), (struct sockaddr *)&client_addr, (socklen_t *)&addrlen)) < 0)
			exit(-1);
		ip = inet_ntoa(client_addr.sin_addr);
		User new_user(new_sock, ip);
		serv.add_user(new_user);
	}
	return (1);
}

int	message_received(Server serv)
{
	std::map<size_t, User> *usr_lst = serv.get_users();
	fd_set	tmp_readfds = serv.get_readfds();
	for (std::map<size_t, User>::iterator user = (*usr_lst).begin(); user != (*usr_lst).end(); user++)
	{
		if (FD_ISSET(user->second.get_sock_fd_id(), &tmp_readfds))
		{
			int retval;
			char	buf[512];
			// check if user est encore co
			// si non, close socket, set a 0
			if ((retval = recv(user->second.get_sock_fd_id() , buf, 512, 0)) == 0)
			{
				std::string content = user->second.get_nickname() + "!" + user->second.get_ip_address() + " QUIT :user disconnected";
				user->second.send(content, (size_t)0, true);
			}
			else
			{
				buf[retval] = '\0';
				// Message message = message_parse(buf);
				// user->second.send();
			}
		}
	
	}
	return (1);
}//return message

int	main(int ac, char **av)
{
	if (ac < 3 || ac > 4)
		return (1);
	std::string		con_info(av[1]);
	std::list<std::string> 	optional = parse_optionnal_arg(con_info);
	int 			i = optional.empty() ? 1 : 2;
	
	//adapte le constructeur au besoin du pdf
	Server serv(atoi(av[i]), av[i+1]); //hardcodé car on s'occupera plus tard des connection inter serveur
	while(true)
	{
		if (init_listen(serv) < 0)
			exit(-1);
		incoming_connection(serv);
		message_received(serv);
	}
	return (0);
}