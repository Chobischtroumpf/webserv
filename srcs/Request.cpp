#include "Request.hpp"

HttpRequest::HttpRequest(const HttpRequest& other)
{
	*this = other;
}

HttpRequest&	HttpRequest::operator=(const HttpRequest & other) {
	if (this != &other)
	{
		this->_method = other.GetMethod();
		this->_headers = other.GetHeaders();
		this->_version = other.GetVersion();
		this->_body = other.GetBody();
	}
    return *this;
}

HttpRequest::HttpRequest(std::string req)
{

}

void HttpRequest::ParseMethodVersion()
{

}

void HttpRequest::ParseHeader()
{

}

void HttpRequest::ParseBody()
{

}
