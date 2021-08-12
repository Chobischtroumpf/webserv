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
		//this->_header_fields = other->GetHeaderFields();
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
	ValidateRequest();
	DisplayHeader();
}

void HttpRequest::ParseHeader()
{
	std::list<std::string> splitted_header; 
	std::list<std::string> line; 
	splitted_header = splitString(_header, "\r\n");
	line = splitString(splitted_header.front(), " "); // first_line[0] == Method, first_line[1] == Path, first_line[2] == version 

	_method = line.front();
	line.pop_front();
	_path = line.front();
	_version = line.back();

	splitted_header.pop_front(); //Remove first line
	
	while (!splitted_header.empty())
	{
		std::string key;
		std::string value;

		int index = splitted_header.front().find(':');
		key = splitted_header.front().substr(0, index);
		value = splitted_header.front().substr(index + 1);

		//std::cout << "first = "  << trim(key, " \r\n") << std::endl << "second = " << trim(value, " \r\n") << std::endl;
		this->_header_fields[trim(key, " \r\n")] = trim(value, " \r\n");   // fills map
		//std::cout << _header_fields[key];
		splitted_header.pop_front();
	}
	
}

void HttpRequest::DisplayHeader()
{
	
	std::map<std::string, std::string>::const_iterator	it;

	std::cout << "Method : " << GetMethod() << " |\tHTTP version : ";
	std::cout << GetVersion() << '\n';
	std::cout << "Path : " << GetPath() << '\n';

	for (it = GetHeaderFields().begin(); it != GetHeaderFields().end(); it++)
		std::cout << it->first << ": " << it->second << '\n';

	std::cout << '\n' << "Request body :\n" << GetBody() << '\n';
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

std::map<std::string,std::string>& HttpRequest::GetHeaderFields()
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

std::string		HttpRequest::GetPath() const
{
	return this->_path;
}

bool	HttpRequest::CheckMethod() const
{
	if (_method.compare("GET") && _method.compare("DELETE") && _method.compare("POST"))
		return false;
	DEBUG("Method ok")
	return true;
}

bool	HttpRequest::CheckVersion() const
{
	if (_version.compare("HTTP/1.0") && _version.compare("HTTP/1.1"))
		return false;
	DEBUG("Version ok")
	return true;
}

//bool	HttpRequest::CheckPath() const {}
//bool	HttpRequest::CheckHeader() const {}
//bool	HttpRequest::CheckBody() const {}


bool			HttpRequest::ValidateRequest()
{
	CheckMethod();
	CheckVersion();
	//HttpRequest::CheckPath();
	//HttpRequest::CheckHeader();
	//HttpRequest::CheckBody();
	return true;
}