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

Response::~Response()
{
}

///////////////////////////////////
///			  Methods			///
///////////////////////////////////

void	Response::setError(Config::server server_config)
{
	this->_response_body = getErrorPage(server_config);
	this->_header.setErrorCode(_error_code);
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

std::string getFileDate(void)
{
	std::time_t t = std::time(0);
   	tm *ltm = localtime(&t);
	char buffer[80];
	strftime(buffer,80,"%d_%b_%Y_%Hh_%Mm_%Ss",ltm);
	std::string str_buf(buffer);
	return (std::string("file_") + trim(str_buf, " "));
}

void	Response::postMethod(Request &request, Config::server &server_config)
{
	std::string filename;
	std::string file_content;
	if (request.getSplit())
	{
		DEBUG("POST")
		std::list<std::string> parts = splitString(request.getBody(), request.getBoundary());
		for (std::list<std::string>::iterator it = parts.begin(); it != parts.end(); it++)
			if ((*it).find("filename") == std::string::npos)
				parts.erase(it);
		for (std::list<std::string>::iterator it = parts.begin(); it != parts.end(); it++)
		{
			size_t pos = (*it).find("filename") + 9;
			size_t endl = (*it).find("\r\n", pos);
			std::string tmp = (*it).substr(pos, endl - pos);
			filename = trim(tmp, "\"");
			file_content =(*it).substr((*it).find("\r\n\r\n") + 4, (*it).length());
			trim(file_content, "-");
		}
	}
	int fd = 0;
	if (filename.empty())
		filename = getFileDate();
	std::string tmp_upload = server_config.root + ltrim(request.getLocation().upload_path, "./") + filename; 
	std::cout << tmp_upload << std::endl;
	if (isDir(request.getPathOnMachine()))
	{
		_error_code = 404;
		setError(server_config);
		return ;
	}
	if ((fd = open(tmp_upload.c_str(), O_CREAT | O_TRUNC | O_WRONLY, 0777)) == -1)
	{
		_error_code = 500;
		setError(server_config);
	}
	else 
	{	
		if (request.getSplit())
			write(fd, file_content.c_str() , file_content.length() );
		else
			write(fd, request.getBody().c_str() , request.getBody().length());
		close(fd); 
		readFile(request.getPathOnMachine(), &_response_body);
	}
	(void)request;
	(void)server_config;
}

void	Response::deleteMethod(Request &request)
{
	if (!file_exists(request.getPathOnMachine()))
		_error_code = 204;
	else
	{
		if (remove(request.getPathOnMachine().c_str()))
			_error_code = 202;
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
	//std::cout << path << std::endl;
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



