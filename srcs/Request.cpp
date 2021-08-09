# include "General.hpp"

HttpRequest::HttpRequest()
{}

HttpRequest::~HttpRequest()
{}

HttpRequest::HttpRequest(const HttpRequest& other)
{
	*this = other;
}

HttpRequest&	HttpRequest::operator=(const HttpRequest & other) {
	if (this != &other)
	{
		this->_method = other.GetMethod();
		this->_version = other.GetVersion();
		this->_header_fields = other.GetHeaderFields();
		this->_header = other.GetHeader();
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
	SplitHeadBody();
	ParseHeader();
}

void HttpRequest::ParseFirstLine()
{

}

void HttpRequest::ParseHeader()
{
	std::list<std::string> splitted_header; 
	std::list<std::string> first_line; 
	splitted_header = splitString(_header, "\r\n");
	first_line = splitString(splitted_header.front(), " "); // first_line[0] == Method, first_line[1] == Path, first_line[2] == version 

	_method = first_line.front();
	first_line.pop_front();
	_path = first_line.front();
	_version = first_line.back();
	
	std::cout << "Method : " << _method << ", Path : " << _path << ", version : " << _version << std::endl; 
}

void HttpRequest::SplitHeadBody()
{
	std::list<std::string> head_body;

	head_body = splitString(this->_raw, "\r\n\r\n");
	this->_header = head_body.front();
	this->_body = head_body.back();
}

std::string		HttpRequest::GetMethod() const
{
	return this->_method;
}

std::string		HttpRequest::GetBody() const
{
	return this->_body;
}

std::map<std::string,std::string> HttpRequest::GetHeaderFields() const
{
	return this->_header_fields;
}

std::string		HttpRequest::GetHeader() const
{
	return this->_header;
}

std::string		HttpRequest::GetVersion() const
{
	return this->_version;
}

std::string		HttpRequest::GetRaw() const
{
	return this->_raw;
}