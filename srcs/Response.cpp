#include "Response.hpp"

Response::Response()
{}

Response::Response(Response &Other)
{
	this->header = Other.getResponseHeaderObj();
}

std::string	Response::setErrorCode(int code)
{
	std::string string = "";
	switch (code)
	{
		case 400:
			return(getErrorFile(400));
		case 403:
			return(getErrorFile(403));
		case 404:
			return(getErrorFile(404));
		case 405:
			return(getErrorFile(405));
		case 413:
			return(getErrorFile(413));
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
	
	if ((this->response_body = setErrorCode(request.getCode())) == "")
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

ResponseHeader &Response::getMethod(HttpRequest request, Config::server &server_config, ResponseHeader &header)
{
	
}
ResponseHeader &Response::postMethod(HttpRequest request, Config::server &server_config, ResponseHeader &header)
{
	
}
ResponseHeader &Response::deleteMethod(HttpRequest request, Config::server &server_config, ResponseHeader &header)
{
	
}
