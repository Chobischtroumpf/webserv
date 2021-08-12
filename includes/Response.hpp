#ifndef RESPONSE_HPP
#define RESPONSE_HPP
#include "General.hpp"

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
		Response(HttpRequest request, Config::server server_config);


		std::string		setErrorCode(int code);
		std::string		getResponse(void);
		std::string		getResponseBody(void);
		std::string		getResponseHeader(void);
		ResponseHeader	&getResponseHeaderObj(void);
		void			getMethod(HttpRequest request, Config::server &server_config);
		void			postMethod(HttpRequest request, Config::server &server_config);
		void			deleteMethod(HttpRequest request, Config::server &server_config);
};

#endif 