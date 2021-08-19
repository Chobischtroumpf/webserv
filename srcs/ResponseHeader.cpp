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
	_errors[100]= "Continue";
	_errors[200]= "OK";
	_errors[201]= "Created";
	_errors[400]= "No Content";
	_errors[401]= "Bad Request";
	_errors[403]= "Forbidden";
}
