#include "Response.hpp"

Response::Response()
{}

Response::Response(Response &Other)
{
	this->header = Other.getResponseHeaderObj();
}

std::string	Response::setErrorCode(Config::server server_config)
{
	std::string string = "";
	switch (error_code)
	{
		case 400:
			return(getErrorFile(400, server_config));
		case 403:
			return(getErrorFile(403, server_config));
		case 404:
			return(getErrorFile(404, server_config));
		case 405:
			return(getErrorFile(405, server_config));
		case 413:
			return(getErrorFile(413, server_config));
		default:
			break;
	}
	return (string);
}

Response::Response(HttpRequest request, Config::server server_config)
{
	// std::map<std::string, std::string> headers = request.GetHeaderFields();
	// check httpRequest for method
	std::string method = request.GetMethod();
	error_code = request.getCode();
	
	if ((this->response_body = setErrorCode(server_config)) == "")
	{
		if (method == "GET")
			getMethod(request, server_config);
		else if (method == "POST")
			postMethod(request, server_config);
		else if (method == "DELETE")
			deleteMethod(request, server_config);
	}
	
}

std::string Response::getResponse(void)
{
	return (response_header + response_body);
}

std::string Response::getResponseBody(void)
{
	return (response_body);
}

std::string Response::getResponseHeader(void)
{
	return (response_header);
}

ResponseHeader	&Response::getResponseHeaderObj(void)
{
	return (header);
}

void	Response::getMethod(HttpRequest request, Config::server &server_config)
{
	(void)request;
	(void)server_config;
}
void	Response::postMethod(HttpRequest request, Config::server &server_config)
{
	(void)request;
	(void)server_config;
}
void	Response::deleteMethod(HttpRequest request, Config::server &server_config)
{
	(void)request;
	(void)server_config;
}
