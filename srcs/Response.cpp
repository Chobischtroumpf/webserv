#include "Response.hpp"

Response::Response()
{}

Response::Response(Response &Other)
{
	this->header = Other.getResponseHeaderObj();
}

std::string			Response::getErrorPage(int code ,Config::server server_config)
{
	if (!server_config.error_pages[code].empty())
		return(readFile(server_config.error_pages[code]));
	return ("");
}

// std::string	Response::setErrorCode(Config::server server_config)
// {
// 	// std::string string = "";
// 	// return ()
// 	// return (string);
// }

Response::Response(HttpRequest request, Config::server server_config)
{
	// std::map<std::string, std::string> headers = request.GetHeaderFields();
	// check httpRequest for method
	std::string method = request.getMethod();
	//error handling must happen before this
	error_code = 404;
	this->response_body = getErrorPage(error_code, server_config);
	if (!response_body.empty())
	{
		std::ostringstream ss;
		ss << response_body.size();
		this->response_header = "HTTP/1.1 404 Not Found\r\nDate: Wed, 18 Aug 2021 14:15:17 GMT\r\nContent-Type: text/html; charset=UTF-8\r\nContent-Length: " + ss.str() + "\r\n\r\n";
		// if (method == "GET")
		// 	getMethod(request, server_config);
		// else if (method == "POST")
		// 	postMethod(request, server_config);
		// else if (method == "DELETE")
		// 	deleteMethod(request, server_config);
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
