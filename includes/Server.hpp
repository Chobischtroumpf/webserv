#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "General.hpp"

class Server;

class Client
{
	public:
	Client(int sd, std::string address);
	Client &operator=(const Client& Other);
	~Client();
	int		getSD();
	private:
		int				socket;
		std::string		client_address;
		int				option_buffer;
		std::string		request;
};

class SubServ
{
	private:
		Server				&main_serv;
		int					sock_des;
		int					option_buffer;
		struct sockaddr_in	srv_address;
		struct Config::server	server_conf;
		std::list<Client>	client_list;
	public:
		SubServ(Config::server serv, Server *main_serv);
		int					getSD();
		sockaddr_in			getAddress();
		Config::server		getConf();
		std::list<Client>	getClientList();

		Server			getMainServer();
		void			setClientList(Client client);
		void			createSD();
		void			setSockOption();
		void			setSubServNonBlock();
		void			initAddress(int port);
		void			bindSubServ();
		void			socketListener();

		SubServ &operator=(const SubServ& Other);
		~SubServ();
};

class Server
{
	public:

		fd_set				readfds;
		fd_set				writefds;
		int					max_sd;
		std::list<SubServ>	sub_serv;

		Server(Config config);
		Server(Server& other);

		void	listen_it();
		void	check_connections();
		void	accept_connection(SubServ &s_srv);
		void	UpAndDownLoad(SubServ &s_srv);
		
//displays
		fd_set						get_readfds();
		sockaddr_in					get_addr();
		std::string					get_pass();
	
		Server &operator=(const Server& Other);
		~Server();

};

#endif
