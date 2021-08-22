#include "ResponseHeader.hpp"

ResponseHeader::ResponseHeader(){}

ResponseHeader::ResponseHeader(Request &request)
{	
	initErrorMap();
	setVersion(request.getVersion());
	setErrorCode(request.getCode());
	_server = "Adorigo and Ncolin's Webserv";
}

ResponseHeader::ResponseHeader(ResponseHeader &Other)
{
	this->_content_language = Other.getContentLanguage();
	this->_content_length = Other.getContentLength();
	this->_content_location = Other.getContentLocation();
	this->_content_type = Other.getContentType();
	this->_http_version = Other.getVersion();
	this->_date = Other.getDate();
	this->_location = Other.getLocation();
	this->_server = Other.getServer();
	this->_transfer_encoding = Other.getTransferEncoding();
	this->_errors = Other.getErrors(); 
}

void ResponseHeader::generate_datetime(void)
{
	std::time_t t = std::time(0);
   	tm *ltm = localtime(&t);
	char buffer[80];
	strftime(buffer,80,"%a, %d %b %Y %H:%M:%S CEST",ltm);
	std::string str_buf(buffer);
	setDate(trim(str_buf, " "));
}

//getters

std::string	ResponseHeader::getHeader(void)
{
	std::string header;
	header = _http_version + " " + std::to_string(_status_code) + " " + _errors[_status_code] + "\r\n" 
			 + "Content-Language: " + _content_language + "\r\n"
			 + "Content-Length: " + std::to_string(_content_length) + "\r\n"
			 + "Content-Location: " + _content_location + "\r\n"
			 + "Content-Type: " + _content_type + "\r\n"
			 + "Date: " + _date + "\r\n"
			 + "Location: " + _location + "\r\n"
			 + "Server: " + _server + "\r\n"
			 + "Transfer-Encoding: " + _transfer_encoding + "\r\n\r\n";
	return (header);
}


std::string	ResponseHeader::getContentLanguage(void) const
{
	return (this->_content_language);
}

int	ResponseHeader::getContentLength(void) const
{
	return (this->_content_length);
}

std::string	ResponseHeader::getContentLocation(void) const
{
	return (this->_content_location);
}

std::string	ResponseHeader::getContentType(void) const
{
	return (this->_content_type);
}

std::string	ResponseHeader::getDate(void) const
{
	return (this->_date);
}

std::string	ResponseHeader::getLocation(void) const
{
	return (this->_location);
}

std::string	ResponseHeader::getServer(void) const
{
	return (this->_server);
}

std::string	ResponseHeader::getTransferEncoding(void) const
{
	return (this->_transfer_encoding);
}

std::string	ResponseHeader::getVersion(void) const
{
	return (this->_http_version);
}

int			ResponseHeader::getReturnCode(void) const
{
	return (this->_status_code );
}

std::map<int, std::string>	ResponseHeader::getErrors(void) const
{
	return (this->_errors);
}

//setters

void		ResponseHeader::setContentLanguage(const std::string& lang)
{
	this->_content_language = lang;
}
void		ResponseHeader::setContentLength(size_t size)
{
	this->_content_length = size;
}

void		ResponseHeader::setContentLocation(int code, const std::string& path)
{
	this->_status_code = code;
	this->_content_location = path;
}

void		ResponseHeader::setContentType(std::string type, std::string path)
{
	(void) path;
	this->_content_type = type;
}

void		ResponseHeader::setDate(std::string date)
{
	this->_date = date;
}

void		ResponseHeader::setErrorCode(int code)
{
	this->_status_code = code;
}

void		ResponseHeader::setLocation(int code, const std::string&redirect)
{
	this->_status_code = code;
	this->_location = redirect;
}

void		ResponseHeader::setServer(void)
{
	this->_server = "Adorigo and Ncolin's Webserv";
}

void		ResponseHeader::setVersion(std::string version)
{
	this->_http_version = version;
}

// void		ResponseHeader::setTransferEncoding(void)
// {
// 	this->
// }


ResponseHeader &ResponseHeader::operator=(const ResponseHeader &src)
{
	this->_content_language = src.getContentLanguage();
	this->_content_length = src.getContentLength();
	this->_content_location = src.getContentLocation();
	this->_content_type = src.getContentType();
	this->_date = src.getDate();
	this->_status_code = src.getReturnCode();
	this->_http_version = src.getVersion();
	this->_location = src.getLocation();
	this->_server = src.getServer();
	this->_transfer_encoding = src.getTransferEncoding();
	this->_errors = src.getErrors(); 
	return (*this);
}

void	ResponseHeader::initErrorMap()
{
	_errors[100] = "Continue";
	_errors[101] = "Switching Protocols";
	_errors[200] = "OK";
	_errors[201] = "Created";
	_errors[202] = "Accepted";
	_errors[203] = "Non-Authoritative Information";
	_errors[204] = "No Content";
	_errors[205] = "Reset Content";
	_errors[206] = "Partial Content";
	_errors[300] = "Multiple Choices";
	_errors[301] = "Moved Permanently";
	_errors[302] = "Found";
	_errors[303] = "See Other";
	_errors[304] = "Not Modified";
	_errors[305] = "Use Proxy";
	_errors[307] = "Temporary Redirect";
	_errors[400] = "Bad Request";
	_errors[401] = "Unauthorized";
	_errors[402] = "Payment Required";
	_errors[403] = "Forbidden";
	_errors[404] = "Not Found";
	_errors[405] = "Method Not Allowed";
	_errors[406] = "Not Acceptable";
	_errors[407] = "Proxy Authentication Required";
	_errors[408] = "Request Timeout";
	_errors[409] = "Conflict";
	_errors[410] = "Gone";
	_errors[411] = "Length Required";
	_errors[412] = "Precondition Failed";
	_errors[413] = "Payload Too Large";
	_errors[414] = "URI Too Long";
	_errors[415] = "Unsupported Media Type";
	_errors[416] = "Range Not Satisfiable";
	_errors[417] = "Expectation Failed";
	_errors[426] = "Upgrade Required";
	_errors[500] = "Internal Server Error";
	_errors[501] = "Not Implemented";
	_errors[502] = "Bad Gateway";
	_errors[503] = "Service Unavailable";
	_errors[504] = "Gateway Timeout";
	_errors[505] = "HTTP Version Not Supported";
}
