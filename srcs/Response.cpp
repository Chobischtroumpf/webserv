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
	_header.generate_datetime();
	if (_error_code >= 400)
		setError(server_config);
	if (method == "GET" && _error_code == 200)
		getMethod(request, server_config);
		// else if (method == "POST")
		// 	postMethod(request, server_config);
		// else if (method == "DELETE")
		// 	deleteMethod(request, server_config);
	
	_header.setContentLength(_response_body.length());
	// std::cout << "LENGTH" << _header.getContentLength() << std::endl;
	this->_response_header = _header.getHeader();
	// std::cout << getResponseHeader() << std::endl << getResponseBody() << std::endl;
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
	//request.displayRequest();
	// std::cout << "PATH " << request.getPath() << std::endl;
	readFile(request.getPath(), &_response_body);
	// std::cout << "BODY" << _response_body << std::endl;
	(void)request;
	(void)server_config;
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
	(void)request;
	(void)server_config;
}

std::string	Response::makeIndex(std::string path)
{
	DIR *dir;
	struct dirent *ent;
	std::string retval = "<html><head></head><body> Webserv's autoindex:" + std::endl;

	if ((dir = opendir(path.c_str())) != NULL);
	{
		while ((ent = readdir (dir)) != NULL)
			retval += "<p><a href=\"" + ent->d_name + "\">" + ent->d_name + "</a></p>\n";
	}
	else
	{
		_error_code = 403;
		return ("");
	}
}
