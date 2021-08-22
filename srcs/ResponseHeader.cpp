#include "ResponseHeader.hpp"

ResponseHeader::ResponseHeader(){}

ResponseHeader::ResponseHeader(Request request)
{	
	setVersion(request.getVersion());
	_status_code = request.getCode();
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

std::string	ResponseHeader::getHeader(void)
{
	std::string header;

	header = _http_version + _status_code + " OK \r\n"  
			 +	"Content-Language: " + _content_language + "\r\n"
			 + "Content-Length: " + _content_length + "\r\n"
			 + "Content-Location: " + _content_location + "\r\n"
			 + "Content-Type: " + _content_type + "\r\n"
			 + "Date: " + _date + "\r\n"
			 + "Location: " + _location + "\r\n"
			 + "Server: " + _server + "\r\n"
			 + "Transfer-Encoding: " + _transfer_encoding + "\r\n\r\n";
	return (header);
}

void ResponseHeader::generate_datetime(void)
{
	std::time_t t = std::time(0);   // get time now
   	tm *ltm = localtime(&t);
	char buffer[80];
	strftime(buffer,80,"%a, %d %b %Y %H:%M:%S CEST",ltm);
	std::string str_buf(buffer);
	setDate(trim(str_buf, " "));
  	std::cout << getDate() << std::endl;
}

std::string	ResponseHeader::getContentLanguage(void) const
{
	return (this->_content_language);
}

std::string	ResponseHeader::getContentLength(void) const
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

std::string	ResponseHeader::getReturnCode(void) const
{
	return (this->_status_code );
}

std::map<int, std::string>	ResponseHeader::getErrors(void) const
{
	return (this->_errors);
}

void		ResponseHeader::setDate(std::string date)
{
	this->_date = date;
}

void		ResponseHeader::setVersion(std::string version)
{
	this->_http_version = version;
}

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
	errors[100] = "Continue";
	errors[101] = "Switching Protocols";
	errors[200] = "OK";
	errors[201] = "Created";
	errors[202] = "Accepted";
	errors[203] = "Non-Authoritative Information";
	errors[204] = "No Content";
	errors[205] = "Reset Content";
	errors[206] = "Partial Content";
	errors[300] = "Multiple Choices";
	errors[301] = "Moved Permanently";
	errors[302] = "Found";
	errors[303] = "See Other";
	errors[304] = "Not Modified";
	errors[305] = "Use Proxy";
	errors[307] = "Temporary Redirect";
	errors[400] = "Bad Request";
	errors[401] = "Unauthorized";
	errors[402] = "Payment Required";
	errors[403] = "Forbidden";
	errors[404] = "Not Found";
	errors[405] = "Method Not Allowed";
	errors[406] = "Not Acceptable";
	errors[407] = "Proxy Authentication Required";
	errors[408] = "Request Timeout";
	errors[409] = "Conflict";
	errors[410] = "Gone";
	errors[411] = "Length Required";
	errors[412] = "Precondition Failed";
	errors[413] = "Payload Too Large";
	errors[414] = "URI Too Long";
	errors[415] = "Unsupported Media Type";
	errors[416] = "Range Not Satisfiable";
	errors[417] = "Expectation Failed";
	errors[426] = "Upgrade Required";
	errors[500] = "Internal Server Error";
	errors[501] = "Not Implemented";
	errors[502] = "Bad Gateway";
	errors[503] = "Service Unavailable";
	errors[504] = "Gateway Timeout";
	errors[505] = "HTTP Version Not Supported";
}
