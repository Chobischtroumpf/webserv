#include "Response.hpp"

Response::Response(){}

Response::Response(Response &Other)
{
	this->_header = Other.getResponseHeaderObj();
}

std::string			Response::getErrorPage(Config::server server_config)
{
	std::string ret_val;
	if (!server_config.error_pages[_error_code].empty())
		if (readFile(server_config.error_pages[_error_code], &ret_val) < 0)
			return ("<html>the file you were looking for does not exist</html>");
	return (ret_val);
}

void	Response::setError(Config::server server_config)
{
	this->_response_body = getErrorPage(server_config);
	_header.setContentLength(this->_response_body.size());
}

Response::Response(Request &request)
{
	Config::server server_config = request.getConf();
	std::string method = request.getMethod();
	_error_code = request.getCode();
	this->_header = ResponseHeader(request);
	if (method == "GET")
		getMethod(request, server_config);
	else if (method == "POST")
		postMethod(request, server_config);
	else if (method == "DELETE")
		deleteMethod(request, server_config);
	fillHeader();
	this->_response_header = _header.getHeader();
}

void 		Response::fillHeader()
{
	_header.setContentLength(_response_body.length());
	_header.generate_datetime();
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

void	Response::getMethod(Request &request, Config::server &server_config)
{
	DEBUG("GET")
	if (_error_code == 200)
		readFile(request.getPath(), &_response_body);
	else
		setError(server_config);
	if (_error_code == 500) // if first readfile fails, we have to put _error_code to 500
		setError(server_config);
}
void	Response::postMethod(Request &request, Config::server &server_config)
{
	DEBUG("POST")
	(void)request;
	(void)server_config;
}
void	Response::deleteMethod(Request &request, Config::server &server_config)
{
	DEBUG("DELETE")
	//check if file exist . If not -> 204
	std::cout << remove(request.getPath().c_str()) << std::endl;
	// if remove fails -> 202
	// if remove succeed -> 200
	
	(void)request;
	(void)server_config;
}
