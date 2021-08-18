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
