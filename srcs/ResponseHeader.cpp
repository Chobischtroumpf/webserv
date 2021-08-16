#include "ResponseHeader.hpp"

ResponseHeader::ResponseHeader()
{
}

ResponseHeader::ResponseHeader(ResponseHeader &Other)
{
	this->content_language = Other.getContentLanguage();
	this->content_length = Other.getContentLength();
	this->content_location = Other.getContentLocation();
	this->content_type = Other.getContentType();
	this->date = Other.getDate();
	this->location = Other.getLocation();
	this->server = Other.getServer();
	this->transfer_encoding = Other.getTransferEncoding();
	this->errors = Other.getErrors(); 
	
}

std::string	ResponseHeader::getHeader(void)
{
	std::string header;

	header = "Content-Language: " + content_language + "\r\n"
			 + "Content-Length: " + content_length + "\r\n"
			 + "Content-Location: " + content_location + "\r\n"
			 + "Content-Type: " + content_type + "\r\n"
			 + "Date: " + date + "\r\n"
			 + "Location: " + location + "\r\n"
			 + "Server: " + server + "\r\n"
			 + "Transfer-Encoding: " + transfer_encoding + "\r\n\r\n";
	return (header);
}

std::string	ResponseHeader::getContentLanguage(void) const
{
	return (this->content_language);
}

std::string	ResponseHeader::getContentLength(void) const
{
	return (this->content_length);
}

std::string	ResponseHeader::getContentLocation(void) const
{
	return (this->content_location);
}

std::string	ResponseHeader::getContentType(void) const
{
	return (this->content_type);
}

std::string	ResponseHeader::getDate(void) const
{
	return (this->date);
}

std::string	ResponseHeader::getLocation(void) const
{
	return (this->location);
}

std::string	ResponseHeader::getServer(void) const
{
	return (this->server);
}

std::string	ResponseHeader::getTransferEncoding(void) const
{
	return (this->transfer_encoding);
}

std::map<int, std::string>	ResponseHeader::getErrors(void) const
{
	return (this->errors);
}

ResponseHeader &ResponseHeader::operator=(const ResponseHeader &src)
{
	this->content_language = src.getContentLanguage();
	this->content_length = src.getContentLength();
	this->content_location = src.getContentLocation();
	this->content_type = src.getContentType();
	this->date = src.getDate();
	this->location = src.getLocation();
	this->server = src.getServer();
	this->transfer_encoding = src.getTransferEncoding();
	this->errors = src.getErrors(); 
	return (*this);
}

void	ResponseHeader::initErrorMap()
{
	errors[100]= "Continue";
	errors[200]= "OK";
	errors[201]= "Created";
	errors[400]= "No Content";
	errors[401]= "Bad Request";
	errors[403]= "Forbidden";
}
