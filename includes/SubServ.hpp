#ifndef SUBSERV_HPP
# define SUBSERV_HPP
# include "General.hpp"
# include "Server.hpp"
# include "Client.hpp"

class Server;

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

#endif
