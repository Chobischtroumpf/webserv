#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "General.hpp"
# include "Request.hpp"
# include "ResponseHeader.hpp"

class Response
{
	private:
		ResponseHeader	header;
		int				error_code;
		std::string		response_body;
		std::string		response_header;
	public:
		Response();
		Response(Response &Other);
		Response(Request request, Config::server server_config);

		std::string		getErrorFile(int code, Config::server server_config);
		std::string		setErrorCode(Config::server server_config);
		std::string		getResponse(void);
		std::string		getResponseBody(void);
		std::string		getResponseHeader(void);
		ResponseHeader	&getResponseHeaderObj(void);
		void			getMethod(Request request, Config::server &server_config);
		void			postMethod(Request request, Config::server &server_config);
		void			deleteMethod(Request request, Config::server &server_config);
};

#endif 