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

std::string	ResponseHeader::getContentLanguage(void)
{
	return (this->content_language);
}

std::string	ResponseHeader::getContentLength(void)
{
	return (this->content_length);
}

std::string	ResponseHeader::getContentLocation(void)
{
	return (this->content_location);
}

std::string	ResponseHeader::getContentType(void)
{
	return (this->content_type);
}

std::string	ResponseHeader::getDate(void)
{
	return (this->date);
}

std::string	ResponseHeader::getLocation(void)
{
	return (this->location);
}

std::string	ResponseHeader::getServer(void)
{
	return (this->server);
}

std::string	ResponseHeader::getTransferEncoding(void)
{
	return (this->transfer_encoding);
}

std::map<int, std::string>	ResponseHeader::getErrors(void)
{
	return (this->errors);
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
