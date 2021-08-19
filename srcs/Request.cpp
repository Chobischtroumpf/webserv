#include "Request.hpp"

Request::Request()
{}

Request::~Request()
{}

Request::Request(const Request& other)
{
	*this = other;
}

Request&	Request::operator=(const Request & other) {
	if (this != &other)
	{
		this->_method = other.getMethod();
		this->_version = other.getVersion();
		//this->_header_fields = other->GetHeaderFields();
		this->_header = other.getHeader();
		this->_body = other.getBody();
		this->_raw = other.getRaw();
	}
    return *this;
}

Request::Request(std::string req, Config::server conf)
{
	this->_return_code = 200;
	this->_raw = req;
	this->_method = "";
	this->_version = "";
	this->_body = "";
	this->_conf = conf; 
	splitHeadBody();
	parseHeader();
	std::cout << "Request valid : " << validateRequest(conf) << std::endl;
	makePath(conf);
	// DisplayRequest();
	checkFile();
	std::cout << "Path : " << _path << std::endl;
}

void Request::parseHeader()
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

void Request::displayRequest()
{
	
	std::map<std::string, std::string>::const_iterator	it;

	std::cout << "Method : " << getMethod() << " |\t version : ";
	std::cout << getVersion() << '\n';
	std::cout << "Path : " << getPath() << '\n';

	for (it = getHeaderFields().begin(); it != getHeaderFields().end(); it++)
		std::cout << it->first << ": " << it->second << '\n';

	std::cout << '\n' << "Request body :\n" << getBody() << '\n';
}

void Request::splitHeadBody()
{
	std::list<std::string> head_body;

	head_body = splitString(this->_raw, "\r\n\r\n");
	this->_header = head_body.front();
	this->_body = trim(head_body.back(), " \r\n");
}

std::string		Request::getMethod() const
{
	return this->_method;
}

std::string		Request::getBody() const
{
	return this->_body;
}

std::map<std::string,std::string>& Request::getHeaderFields()
{
	return this->_header_fields;
}

std::string		Request::getHeader() const
{
	return this->_header;
}

std::string		Request::getVersion() const
{
	return this->_version;
}

std::string		Request::getRaw() const
{
	return this->_raw;
}

std::string		Request::getPath() const
{
	return this->_path;
}

int				Request::getCode() const
{
	return this->_return_code;
}

Config::server	Request::getConf() const
{
	return this->_conf;
}


bool	Request::checkMethod()
{
	if (_method.compare("GET") && _method.compare("DELETE") && _method.compare("POST"))
	{
		_return_code = 400;
		return false;
	}
	return true;
}

bool	Request::checkVersion()
{
	if (_version.compare("HTTP/1.0") && _version.compare("HTTP/1.1"))
	{
		_return_code = 400;
		return false;
	}
	return true;
}


bool	Request::checkPath(Config::server conf)
{
	int pos = _path.rfind("/");
	std::string tmp_path = _path.substr(0, pos + 1); // Right trim up to '/'
	// set une variable config::server.locations correct_location
	// OpTiMiSeR lE cOdE -> rEfErEnCe 
	std::cout << "1 tmp_path : " << tmp_path << std::endl;

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
			std::cout << "2 tmp_path : " << tmp_path << std::endl;
			if (tmp_path == it->first)
			{

				_location = it->second;
				//_path = tmp_path;
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

void	Request::makePath(Config::server serv_conf)
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

bool			Request::checkFile()
{
	// It only works if the path given in the config file is absolute
	struct stat info;
	std::cout << stat(_path.c_str(), &info) << std::endl;
	if (stat(_path.c_str(), &info) != 0)
		return (-1);
	else
	{
		if (S_ISREG(info.st_mode))
		{
			std::cout << "This is a file" << std::endl;
			return (1);
		}
		else if (S_ISDIR(info.st_mode))
		{
			std::cout << "This is a directory" << std::endl;
			return (0);
		}
		else
			return (-1);
	}

}

bool			Request::validateRequest(Config::server conf)
{
	return (checkMethod() && checkVersion() && checkPath(conf));
	//CheckHeaderFields();
}