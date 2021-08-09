#ifndef RESPONSE_HPP
#define RESPONSE_HPP
#include "General.hpp"

class Response
{
	private:
		ResponseHeader	header;
		std::string		response_body;
		std::string		response_header;
	public:
		Response();
		Response(Response &Other);
		Response(HttpRequest request, Config::server server_config);

		std::string		getResponse(void);
		std::string		getResponseBody(void);
		std::string		getResponseHeader(void);
		ResponseHeader	getResponseHeaderObj(void);
};

#endif 