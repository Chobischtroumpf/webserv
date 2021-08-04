#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "General.hpp"

class Server;

class Client
{
	public:
		Client(int sd, std::string address);
		int			getSD(void);
		std::string	getRequest(void);
		void		setReceived(bool);
		bool		requestReceived(void);
		int			receiveRequest(void);

		Client &operator=(const Client& Other);
		friend bool operator==(const Client& lhs, const Client& rhs);
		~Client();
	private:
		int				socket;
		std::string		client_address;
		int				option_buffer;
		std::string		request;
		bool			is_received;
};
		// friend bool &Client::operator==(const Client& lhs, const Client& rhs);

class SubServ
{
	private:
		Server					&main_serv;
		int						sock_des;
		int						option_buffer;
		struct sockaddr_in		srv_address;
		struct Config::server	server_conf;
		std::list<Client>		client_list;
	public:
		SubServ(Config::server serv, Server *main_serv);
		int					getSD();
		sockaddr_in			getAddress();
		Config::server		getConf();
		std::list<Client>	&getClientList();

		Server			getMainServer();
		int				receiveRequest(int sd, Client client);
		void			setClientList(const Client &client);
		void			popClient(const Client &client);
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

		void	listenIt();
		void	checkConnections();
		void	acceptConnection(SubServ &s_srv);
		void	upAndDownLoad(SubServ &s_srv);

//displays
		fd_set						getReadfds();
		sockaddr_in					getAddr();
		std::string					getPass();
	
		Server &operator=(const Server& Other);
		~Server();

};

#endif
