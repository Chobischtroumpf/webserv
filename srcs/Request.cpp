#include "Request.hpp"

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

HttpRequest::HttpRequest(std::string req, Config::server conf)
{
	this->_return_code = 200;
	this->_raw = req;
	this->_method = "";
	this->_version = "";
	this->_body = "";
	//for (std::map<std::string, Config::location>::iterator it = conf.locations.begin(); it != conf.locations.end(); it++)
	//{
	//	this->_available_locations.push_back(it->first);
	//}
	SplitHeadBody();
	ParseHeader();
	std::cout << "Request valid : " << ValidateRequest(conf) << std::endl;
	MakePath(conf);
	// DisplayRequest();
	std::cout << "Path : " << _path << std::endl;
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
		this->_header_fields[trim(key, " \r\n")] = trim(value, " \r\n");
		splitted_header.pop_front();
	}
}

void HttpRequest::DisplayRequest()
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
	this->_body = trim(head_body.back(), " \r\n");
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

int				HttpRequest::GetCode() const
{
	return this->_return_code;
}

bool	HttpRequest::CheckMethod()
{
	if (_method.compare("GET") && _method.compare("DELETE") && _method.compare("POST"))
	{
		_return_code = 400;
		return false;
	}
	return true;
}

bool	HttpRequest::CheckVersion()
{
	if (_version.compare("HTTP/1.0") && _version.compare("HTTP/1.1"))
	{
		_return_code = 400;
		return false;
	}
	return true;
}


bool	HttpRequest::CheckPath(Config::server conf)
{
	int pos = _path.rfind("/");
	std::string tmp_path = _path.substr(0, pos); // Right trim up to '/'
	// set une variable config::server.locations correct_location
	// OpTiMiSeR lE cOdE -> rEfErEnCe 
	for (std::map<std::string, Config::location>::iterator it = conf.locations.begin(); it != conf.locations.end(); it++)
	{
		if (tmp_path == it->first)
		{
			_location = it->second;
			std::cout << "The whole path corresponds" << std::endl;
			return true;
		}
	}
	while((pos = tmp_path.rfind("/")))
	{
		tmp_path = _path.substr(0, pos + 1);
		for (std::map<std::string, Config::location>::iterator it = conf.locations.begin(); it != conf.locations.end(); it++)
		{
			if (tmp_path == it->first)
			{
				_location = it->second;
				std::cout << "A part of the path corresponds" << std::endl;
				return true;
			}
		}
		tmp_path = _path.substr(0, pos);
	}
	std::cout << "Couldn't find a corresponding location" << std::endl;
	_return_code = 404;

	return false;
}

void	HttpRequest::MakePath(Config::server serv_conf)
{
	std::string root_without_final_slash;
	int length_root = serv_conf.root.length();
	int pos = serv_conf.root.rfind('/');
	if ((length_root - 1) == pos)
		root_without_final_slash = serv_conf.root.substr(0, length_root - 1);
	else
		root_without_final_slash = serv_conf.root;
	std::string path_no_file = _path.substr(0, _path.rfind('/')+1);
	std::string file = _path.substr(_path.rfind('/')+1);
	_path = root_without_final_slash;
	_path += serv_conf.locations[path_no_file].root;
	_path += file;
	std::cout << _path << std::endl;
}

//bool			HttpRequest::CheckFile()
//{

//// -1 : stat failed or nor a file or directory
//// 0  : is a directory
//// 1  : is a file

//	struct stat info;
//	if (stat(_path.c_str(), &info) != 0)
//		return (-1);
//	else
//	{
//		if (S_ISREG(info.st_mode))
//			return (1);
//		else if (S_ISDIR(info.st_mode))
//			return (0);
//		else
//			return (-1);
//	}

//}

bool			HttpRequest::ValidateRequest(Config::server conf)
{
	return (CheckMethod() && CheckVersion() && CheckPath(conf));
	//CheckHeaderFields();
}