#include "Response.hpp"

Response::Response(){}

Response::Response(Response &Other)
{
	this->_header = Other.getResponseHeaderObj();
}

std::string			Response::getErrorFile(int code ,Config::server server_config)
{
	(void) code;
	(void) server_config;
	std::string ret = std::string("Temporary error handling");
	return (ret);
}

std::string	Response::setErrorCode(Config::server server_config)
{
	std::string string = "";
	switch (_error_code)
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

Response::Response(Request request)
{
	// std::map<std::string, std::string> headers = request.GetHeaderFields();
	// check Request for method
	Config::server server_config = request.getConf();
	std::string method = request.getMethod();
	this->_header = ResponseHeader(request);
	_header.generate_datetime();
	this->_response_header = _header.getHeader();
	if ((this->_response_body = setErrorCode(server_config)) == "")
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
	return (_response_header + _response_body);
}

std::string Response::getResponseBody(void)
{
	return (_response_body);
}

std::string Response::getResponseHeader(void)
{
	return (_response_header);
}

ResponseHeader	&Response::getResponseHeaderObj(void)
{
	return (_header);
}

void	Response::getMethod(Request request, Config::server &server_config)
{
	DEBUG("GET")
	//request.displayRequest();
	(void)request;

	(void)server_config;
}
void	Response::postMethod(Request request, Config::server &server_config)
{
	DEBUG("POST")
	(void)request;
	(void)server_config;
}
void	Response::deleteMethod(Request request, Config::server &server_config)
{
	DEBUG("DELETE")
	(void)request;
	(void)server_config;
}
