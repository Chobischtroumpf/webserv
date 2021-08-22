#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "General.hpp"
# include "Request.hpp"
# include "ResponseHeader.hpp"

class Response
{
	private:
		ResponseHeader	_header;
		std::string		_datetime;
		int				_error_code;
		std::string		_response_body;
		std::string		_response_header;
	public:
		Response();
		Response(Response &Other);
		Response(Request request);

		std::string		getErrorPage(Config::server server_config);
		std::string		setErrorCode(Config::server server_config);
		std::string		getResponse(void);
		std::string		getResponseBody(void);
		std::string		getResponseHeader(void);
		ResponseHeader	&getResponseHeaderObj(void);
		void			setError(Config::server server_config);

		void			getMethod(Request request, Config::server &server_config);
		void			postMethod(Request request, Config::server &server_config);
		void			deleteMethod(Request request, Config::server &server_config);
};

#endif 