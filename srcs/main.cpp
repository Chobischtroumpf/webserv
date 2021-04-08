#include "../includes/General.hpp"

int	main(int ac, char **av)
{
	std::string		con_info(av[1]);
	std::list<std::string> 	optionnal = parse_optionnal_arg(con_info);
	int 			i = optionnal.empty() ? 1 : 2;
	
	//adapte le constructeur au besoin du pdf
	Server serv(atoi(av[i]), av[i+1]); //hardcodé car on s'occupera plus tard des connection inter serveur
	while(true)
	{
		{//reception
			{//init
				std::map<size_t, User> *usr_lst = serv.get_users();
				int	max_sd = serv.get_sock_fd();

				//clear the socket set
				FD_ZERO(&serv.get_readfds());
				//add master socket to set
				FD_SET(serv.get_sock_fd(), &serv.get_readfds());
				//add child sockets to set
				for (std::map<size_t, User>::iterator user = (*usr_lst).begin(); user != (*usr_lst).end(); user++)
				{
					// user == pas bon
					// if (user->second.get_sock_fd_id() == 0)
					// {
					// 	std::map<size_t, User>::iterator tmp = user;
					// 	usr_lst->erase(tmp);
					// 	continue;
					// }
					if (user->second.get_sock_fd_id() > 0)
						FD_SET(user->second.get_sock_fd_id(), &serv.get_readfds());
					if (user->second.get_sock_fd_id() > max_sd)
						max_sd = user->second.get_sock_fd_id();
				}
				//wait for an activity on one of the sockets , timeout is NULL , 
				//so wait indefinitely 
				return (select(max_sd + 1, &serv.get_readfds(), NULL, NULL, NULL));
			}//return : select return

			{//init connection
				int	new_sock;
				int	addrlen = sizeof(serv.get_addr());
				//If something happened on the master socket , 
				//then its an incoming connection 
				if (FD_ISSET(serv.get_sock_fd(), &serv.get_readfds()))
				{
					std::string ip;
					struct sockaddr_in client_addr = serv.get_addr();
					if ((new_sock = accept(serv.get_sock_fd(), (struct sockaddr *)&client_addr, (socklen_t *)&addrlen)) < 0)
						exit(-1);
					ip = inet_ntoa(client_addr.sin_addr);
					User new_user(new_sock, ip);
					serv.add_user(new_user);
				}
			}
		
			{//IO Operation
				//else its some IO operation on some other socket
				std::map<size_t, User> *usr_lst = serv.get_users();
				for (std::map<size_t, User>::iterator user = (*usr_lst).begin(); user != (*usr_lst).end(); user++)
				{
					if (FD_ISSET(user->second.get_sock_fd_id(), &serv.get_readfds()))
					{
						int retval;
						char	buf[512];
						// check if user est encore co
						// si non, close socket, set a 0
						if ((retval = recv(user->second.get_sock_fd_id() , buf, 512, NULL)) == 0)
						{
							std::string content = user->second.get_nickname() + "!" + user->second.get_ip_address() + " QUIT :user disconnected";
							user->second.send(content, (size_t)0, true);
						}
						else
						{
							buf[retval] = '\0';
							Message message = message_parse(buf);
							user->second.send();
						}
					}

				}
			}//return message
		}
	}
	return (0);
}