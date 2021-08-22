#include "Response.hpp"

Response::Response(){}

Response::Response(Response &Other)
{
	this->_header = Other.getResponseHeaderObj();
}

std::string			Response::getErrorPage(Config::server server_config)
{
	if (!server_config.error_pages[_error_code].empty())
		return(readFile(server_config.error_pages[_error_code]));
	return ("");
}

void	Response::setError(Config::server server_config)
{
	this->_response_body = getErrorPage(server_config);
	_header.setContentLength(this->_response_body.size());
}

Response::Response(Request request)
{
	// std::map<std::string, std::string> headers = request.GetHeaderFields();
	// check Request for method
	Config::server server_config = request.getConf();
	std::string method = request.getMethod();

	_error_code = request.getCode();
	this->_header = ResponseHeader(request);
	_header.generate_datetime();
	this->_response_header = _header.getHeader();
		// if (method == "GET")
		// getMethod(request, server_config);
		// else if (method == "POST")
		// 	postMethod(request, server_config);
		// else if (method == "DELETE")
		// 	deleteMethod(request, server_config);
	if (_error_code >= 400)
		setError(server_config);
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
