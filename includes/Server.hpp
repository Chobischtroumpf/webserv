#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "General.hpp"

class Socket
{
	private:
		int					sock_des;
		int					option_buffer;
		struct sockaddr_in	address;
		struct Config::server	server_conf;
	public:
		Socket(Config::server serv);
		int				getSD();
		sockaddr_in		getAddress();
		Config::server	getConf();
		void			createSD(void);
		void			setSockOption();
		void			setSocketNonBlock();
		void			initAddress(int port);

		~Socket();
};


class Server
{
	public:

		fd_set			readfds;
		fd_set			writefds;

		std::list<Socket>	sub_serv;
		Server(Config config);
		void	check_connections(); 
		
//displays

		void	display_users(std::string mode = "all");//display users ['all' || 'connected' || 'disconnected']
		void	display_user(size_t id);
		void	display_chans();
		void	display_chan(size_t id);

//setters

//unsetters

		void	delete_user(size_t id);
		void	delete_channel(size_t id);
		
//getters
		
		fd_set						get_readfds();
		int							get_sock_fd();
		sockaddr_in					get_addr();
		std::string					get_pass();
	
		~Server();

};

#endif
