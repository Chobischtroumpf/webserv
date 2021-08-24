#include "Request.hpp"

Request::Request()
{
}

Request::~Request()
{
}

Request::Request(const Request &other)
{
	*this = other;
}

Request &Request::operator=(const Request &other)
{
	if (this != &other)
	{
		this->_method = other.getMethod();
		this->_version = other.getVersion();
		this->_header_fields = other.getHeaderFields();
		this->_header = other.getHeader();
		this->_body = other.getBody();
		this->_raw = other.getRaw();
	}
	return *this;
}

Request::Request(std::string req, Config::server &conf)
{
	//init request
	this->_status_code = 200;
	this->_raw = req;
	this->_conf = conf;
	this->_method = "";
	this->_version = "";
	this->_header = "";
	this->_body = "";
	this->_path = "";
	this->_header_fields.clear();
	this->_available_locations.clear();
	//build request
	splitHeadBody();
	parseHeader();
	if (validateRequest(conf))
	{
		// std::cout << "request valid" << std::endl;
		std::cout << "path before makepath" << _path << std::endl;
		makePath();
		std::cout << _path << std::endl;
		checkFile();
	}
	//displayRequest();
}

void Request::parseHeader()
{
	std::list<std::string> splitted_header;
	std::list<std::string> line;
	splitted_header = splitString(_header, "\r\n");
	line = splitString(splitted_header.front(), " ");

	_method = line.front();
	line.pop_front();
	_path = line.front();
	_version = line.back();

	splitted_header.pop_front();

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
	std::map<std::string, std::string>::const_iterator it;

	std::cout << "Method : " << getMethod() << '\n';
	std::cout << "Version : " << getVersion() << '\n';
	std::cout << "Path : " << getPath() << '\n';
	std::map<std::string, std::string> header_fields = getHeaderFields();
	for (it = header_fields.begin(); it != header_fields.end(); it++)
		std::cout << it->first << ": " << it->second << '\n';
}

void Request::splitHeadBody()
{
	std::list<std::string> head_body;

	head_body = splitString(this->_raw, "\r\n\r\n");
	this->_header = head_body.front();
	this->_body = trim(head_body.back(), " \r\n");
}

///////////
//getters//
///////////

std::string const &Request::getMethod() const
{
	return this->_method;
}

std::string const &Request::getBody() const
{
	return this->_body;
}

std::map<std::string, std::string> const &Request::getHeaderFields() const
{
	// std::map<std::string, std::string> copy;
	// copy.insert(this->_header_fields.begin(), this->_header_fields.end());
	return _header_fields;
}

std::string const &Request::getHeader() const
{
	return this->_header;
}

std::string const &Request::getVersion() const
{
	return this->_version;
}

std::string const &Request::getRaw() const
{
	return this->_raw;
}

std::string const &Request::getPath() const
{
	return this->_path;
}

int Request::getCode() const
{
	return this->_status_code;
}

Config::server const &Request::getConf() const
{
	return _conf;
}

bool	Request::getAutoIndex() const
{
	return _location.is_autoindex;
}

////////////
//checkers//
////////////

bool Request::checkMethod()
{
	if (_method.compare("GET") && _method.compare("DELETE") && _method.compare("POST"))
	{
		_status_code = 405;
		return false;
	}
	return true;
}

bool Request::checkVersion()
{
	if (_version.compare("HTTP/1.0") && _version.compare("HTTP/1.1"))
	{
		_status_code = 400;
		return false;
	}
	return true;
}

bool Request::checkPath(Config::server &conf)
{
	int pos = _path.rfind("/");
	std::string tmp_path = _path.substr(0, pos + 1);
	for (std::map<std::string, Config::location>::iterator it = conf.locations.begin(); it != conf.locations.end(); it++)
	{
		if (tmp_path == it->first)
		{
			_location = it->second;
			return true;
		}
	}
	while ((pos = tmp_path.rfind("/")))
	{
		tmp_path = _path.substr(0, pos + 1);
		for (std::map<std::string, Config::location>::iterator it = conf.locations.begin(); it != conf.locations.end(); it++)
		{
			if (tmp_path == it->first)
			{
				_location = it->second;
				return true;
			}
		}
		tmp_path = _path.substr(0, pos);
	}
	return false;
}

bool Request::checkFile()
{
	struct stat info;
	if (stat(_path.c_str(), &info) != 0)
		{
			std::cout << strerror(errno) << std::endl;
			_status_code = 500;
			return (-1);
		}
	else
	{
		if (S_ISREG(info.st_mode))
		{
			_status_code = 200;
			return (1);
		}
		else if (S_ISDIR(info.st_mode))
		{
			if (!_location.index.empty())
			{
				std::string tmp = _path + _location.index;
				if (isFile(tmp))
				{
					_path = tmp;
					_status_code = 200;
					return (1);
				}
			}
			if (_location.is_autoindex)
			{
				_status_code = 200;
				DEBUG("autoindex on")
			}
			else
				_status_code = 403;
			return (0);
		}
		else
		{
			_status_code = 404;
			return (-1);
		}
	}
}

void Request::makePath()
{
	std::string root;
	int length_root = _conf.root.length();
	int pos = _conf.root.rfind('/');
	if ((length_root - 1) == pos)
		root = _conf.root.substr(0, length_root - 1);
	else
		root = _conf.root;
	std::string tmp = _path.substr(_location.name.length());
	_path = root += _location.root += tmp;
}

bool Request::validateRequest(Config::server &conf)
{
	return (checkMethod() && checkVersion() && checkPath(conf));
	//CheckHeaderFields();
}