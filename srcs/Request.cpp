#include "Request.hpp"

HttpRequest::HttpRequest(const HttpRequest& other)
{
	*this = other;
}

HttpRequest&	HttpRequest::operator=(const HttpRequest & other) {
	if (this != &other)
	{
		this->_method = other.GetMethod();
		this->_version = other.GetVersion();
		this->_headers = other.GetHeaders();
		this->_body = other.GetBody();
		this->_raw = other.GetRaw();
	}
    return *this;
}

HttpRequest::HttpRequest(std::string req)
{
	this->_raw = req;
	this->_method = "";
	this->_version = "";
	this->_body = "";
}

void HttpRequest::ParseMethodVersion()
{

}

void HttpRequest::ParseHeader()
{
	// Get first word, should be GET, POST or DELETE, otherwise 400, stop parsing
	// Get path
}

void HttpRequest::ParseBody()
{

}

std::string		HttpRequest::GetMethod() const
{
	return this->_method;
}

std::string		HttpRequest::GetBody() const
{
	return this->_body;
}

std::string		HttpRequest::GetVersion() const
{
	return this->_version;
}

std::string		HttpRequest::GetRaw() const
{
	return this->_raw;
}