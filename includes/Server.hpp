#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "General.hpp"
# include "Client.hpp"
# include "SubServ.hpp"

class SubServ;

class Server
{
	public:

		fd_set				readfds; //this one is a temp one that gets modified by select
		fd_set				writefds;
		fd_set				server_read_fd; //this one is the main one, containing all the SubServs and clients
		fd_set				server_write_fd; 
		int					max_sd;
		int					keep_going;
		struct timeval		timeout;
		std::list<SubServ>	sub_serv;

		Server();
		Server(Config config);
		Server(Server& other);

		void							listenIt();
		void							checkConnections();
		void							upAndDownLoad(SubServ &s_srv);
		int								acceptConnection(SubServ &s_srv);
		std::list<Client *>::iterator	removeClient(std::list<Client *>::iterator &client, SubServ &sub_srv);

//displays
		fd_set						getReadfds();
		sockaddr_in					getAddr();
		std::string					getPass();
		std::list<SubServ>			&getSubServ();

	
		Server &operator=(const Server& Other);
		~Server();

};

#endif
