#ifndef CLIENT_HPP
# define CLIENT_HPP
# include "General.hpp"
# include "Request.hpp"

class Client
{
	public:
		Client(int sd, std::string address);
		int			getSocketDesc(void);
		std::string	getRequest(void);
		std::string	getAddress(void);
		Request	getHttpRequest(void);
		void		setReceived(bool);
		void 		setClientNonBlock(void);
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
		Request		request;
		std::string		response_header;
		std::string		response;
};

#endif
