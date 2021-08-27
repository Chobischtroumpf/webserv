#include "Response.hpp"

///////////////////////////////////
///	Constructor and Destructors ///
///////////////////////////////////

Response::Response(){}

Response::Response(Response &Other)
{
	this->_header = Other.getResponseHeaderObj();
}

Response::Response(Request &request)
{
	Config::server server_config = request.getConf();
	std::string method = request.getMethod();
	_error_code = request.getCode();
	this->_header = ResponseHeader(request);
	DEBUG(request.getAutoIndex())
	if (request.hasRedirection() && _error_code == 200)
	{
		_header.setLocation(request.getRedirectionCode(), request.getRedirection());
		_error_code = request.getRedirectionCode();
	}
	if (_error_code >= 300)
		setError(server_config);
	else if (method == "GET")
		getMethod(request, server_config);
	else if (method == "POST")
		postMethod(request, server_config);
	else if (method == "DELETE")
		deleteMethod(request);
	fillHeader();
	this->_response_header = _header.getHeader();
}

///////////////////////////////////
///			  Methods			///
///////////////////////////////////

void	Response::setError(Config::server server_config)
{
	this->_response_body = getErrorPage(server_config);
	_header.setContentLength(this->_response_body.size());
}


void 		Response::fillHeader()
{
	_header.setContentLength(_response_body.length());
	_header.generate_datetime();
}

void	Response::getMethod(Request &request, Config::server &server_config)
{DEBUG("GET")
	if (request.getAutoIndex() && isDir(request.getPathOnMachine()))
		_response_body = makeIndex(request);
	else if (_error_code == 200)
		readFile(request.getPathOnMachine(), &_response_body);
	else
		setError(server_config);
	if (_error_code == 500) // if first readfile fails, we have to put _error_code to 500
		setError(server_config);
}

void	Response::postMethod(Request &request, Config::server &server_config)
{
	DEBUG("POST")
	std::cout << request.getPathOnMachine() << std::endl;
	std::ofstream file;
	file.open(request.getPathOnMachine());
	if (!file.is_open())
	{
		file.close();
		std::cout << "couldn't open file properly" << std::endl;
		_error_code = 409;
		setError(server_config);
	}
	else 
	{
		file << request.getBody() << std::endl;
		file.close(); 
	}
	(void)request;
	(void)server_config;
}

void	Response::deleteMethod(Request &request)
{
	DEBUG("DELETE")

	//check if file exist . If not -> 204
	if (!file_exists(request.getPathOnMachine()))
		_error_code = 204;
	else
	{
		if (remove(request.getPathOnMachine().c_str()))
			_error_code = 202; // request accepted but not executed
		else
			_error_code = 200;
	}
}

std::string			Response::getErrorPage(Config::server server_config)
{
	std::string ret_val;
	if (!server_config.error_pages[_error_code].empty())
		if (readFile(server_config.error_pages[_error_code], &ret_val) < 0)
			return ("<html>the file you were looking for does not exist</html>");
	return (ret_val);
}

std::string	Response::makeIndex(Request &request)
{
	DIR *dir;
	struct dirent *ent;
	std::string retval = "<html><head></head><body> <h1>Webserv's autoindex:</h1>\n";
	std::string path = request.getPathOnMachine();
	std::cout << path << std::endl;
	if ((dir = opendir(path.c_str())) != NULL)
	{
		while ((ent = readdir (dir)) != NULL)
		{
			if (isFile((path+"/"+ent->d_name).c_str()))
			{
				retval += "<p><a href=\"";
				retval += request.getPath() + ent->d_name;
				retval += "\">";
				retval += ent->d_name;
				retval += "</a></p>\n";
			}
			else if (isDir((path+"/"+ent->d_name).c_str()))
			{
				retval += "<p><a href=\"";
				retval += request.getPath() + ent->d_name;
				retval += "/\">";
				retval += ent->d_name;
				retval += "</a></p>\n";
			}
		}
		retval += "</body></html>";
	}
	else
	{
		_error_code = 500;
		return ("");
	}
	return (retval);
}

///////////////////////////////////
///			  Getters			///
///////////////////////////////////


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



