#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "General.hpp"

class Server;

//////////////////////////////////////////////////////////////////////////////////////
// maybe we should had const keyword to our getters for the sake of good practise ? //
//////////////////////////////////////////////////////////////////////////////////////
// yeah maybe we should do that, could be a good idea //
////////////////////////////////////////////////////////

class Client
{
	public:
		Client(int sd, std::string address);
		int			getSocketDesc(void);
		std::string	getRequest(void);
		std::string	getAddress(void);
		HttpRequest	getHttpRequest(void);
		void		setReceived(bool);
		bool		requestReceived(void);
		int			receiveRequest(void);
		void		printClient(void);
		int			sendRequest(void);

		Client &operator=(const Client& Other);
		friend bool operator==(const Client& lhs, const Client& rhs);
		~Client();
	private:
		int				socket;
		std::string		client_address;
		int				option_buffer;
		std::string		raw_request;
		bool			is_received;
		HttpRequest		request;
		std::string		response_header;
		std::string		response;

};

// friend bool &Client::operator==(const Client& lhs, const Client& rhs);

class SubServ
{
	private:
		Server					&main_serv;
		int						sock_desc; // I would rename to SD, it's confusing
		int						option_buffer;
		struct sockaddr_in		srv_address;
		struct Config::server	server_conf;
		std::list<Client>		client_list;
	public:
		SubServ(Config::server serv, Server *main_serv);
		int					getSocketDesc();
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
		void			printSubserv(void);
		void 			printClientList(void);

		SubServ &operator=(const SubServ& Other);
		~SubServ();
};

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
