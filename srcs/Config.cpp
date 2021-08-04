#include "Config.hpp"

std::list<std::string> Config::populateLocationValue() 
{DEBUG("populateLocationValue")
	std::list<std::string> ret;
	ret.push_back("name");
	ret.push_back("root");
	ret.push_back("method");
	ret.push_back("index");
	ret.push_back("upload_path");
	ret.push_back("autoindex");
	ret.push_back("upload_enable");
	ret.push_back("cgi_extension");
	ret.push_back("cgi_path");
	ret.push_back("client_max_body_size");
	return (ret);
};

Config::Config(std::string file)
{DEBUG("CONFIG")
	if (file.compare(file.size() - 5, 5, ".conf") != 0)
		throw ParsingException(0, "Config file needs .conf extention");
	std::string file_content = skipComment(readFile(file));
	size_t starting_pos, pos = 0;
	Config::server serveur;
	this->location_values = populateLocationValue();

	if(countChar('{', file_content) != countChar('}', file_content))
		throw ParsingException(0, "error in config file : unmatched bracket");
	while ((starting_pos = file_content.find("server", pos)) != std::string::npos)
	{
		pos = offsetCutScope(file_content, file_content.find("{", starting_pos));
		serveur = parseServer(file_content.substr(starting_pos, pos));
		logServConfig(serveur); //logging
		this->servers.push_back(serveur);
	}
}

size_t	Config::offsetCutScope(std::string file, size_t starting_pos)
{DEBUG("offsetCutScope")
	std::vector<size_t> pos(2, starting_pos);
	int opening_brace = 1;
	int	closing_brace = 0;
	while (opening_brace != closing_brace && pos[0] <= pos[1])
	{
		if ((pos[0] = file.find("{", pos[0] + 1)) != std::string::npos)
			opening_brace++;
		if ((pos[1] = file.find("}", pos[1] + 1)) != std::string::npos)
			closing_brace++;
	}
	return (pos[1]);
}

bool	checkListen(std::list<std::string> element, Config::server *ret_serv)
{DEBUG("checkListen")
	if (element.front() == "listen")
	{
		if (element.size() != 3)
			throw ParsingException(0, "wrong amount of arguments to listen");
		element.pop_front();
		if (!(isNumber(element.front()) && (ret_serv->port = std::atoi(element.front().c_str())) >=0))
			throw ParsingException(0, element.front() + " is not a valid port");
		element.pop_front();
		ret_serv->host = element.front();
		return (true);
	}
	else
		return (false);
}

bool	checkServerName(std::list<std::string> element, Config::server *ret_serv)
{DEBUG("checkServerName")
	if (element.front() == "server_name")
	{
		if (element.size() < 2)
			throw ParsingException(0, "not enough arguments in server_name");
		element.pop_front();
		ret_serv->names.insert(ret_serv->names.end(), element.begin(), element.end());
	}
	return (!ret_serv->names.empty());
}

bool	checkErrorPage(std::list<std::string> element, Config::server *ret_serv)
{DEBUG("checkErrorPage")
	ssize_t		tmp_err;
	if (element.front() == "error_page")
	{
		if (element.size() != 3)
			throw ParsingException(0, "wrong amount of arguments to error_page");
		tmp_err = -1;
		element.pop_front();
		if (!(isNumber(element.front()) && (tmp_err = std::atoi(element.front().c_str())) >=0))
			throw ParsingException(0, element.front() + " is not a numeric value.");
		element.pop_front();
		ret_serv->error_pages[tmp_err] = element.front();
	}
	return (!ret_serv->error_pages.empty());
}

bool	checkRoot(std::list<std::string> element, Config::server *ret_serv)
{DEBUG("checkRoot")
	if (element.front() == "root")
	{
		if (element.size() != 2)
			throw ParsingException(0, "wrong amount of arguments to root");
		element.pop_front();
		if (*(element.front().begin()) == '/')
			ret_serv->root = element.front();
	}
	return (!ret_serv->root.empty());
}

bool	errorServer(std::list<std::string> element, Config::server *ret_serv)
{DEBUG("errorServer")
	return (!(checkListen(element, ret_serv)
		|| checkServerName(element, ret_serv)
		|| checkErrorPage(element, ret_serv)
		|| checkRoot(element, ret_serv)));
}

Config::server	Config::parseServer(std::string server_scope)
{DEBUG("parseServer")
	size_t	starting_pos = 0;
	size_t	closing_brace;
	Config::server ret_server;
	Config::location tmp_location;
	ret_server.port = 0;
	while ((starting_pos = server_scope.find("location", starting_pos)) != std::string::npos)
	{
		closing_brace = offsetCutScope(server_scope, server_scope.find("{", starting_pos));
		tmp_location = parseLocation(server_scope.substr(starting_pos, closing_brace - starting_pos + 1));
		ret_server.locations[tmp_location["name"].front()] = tmp_location;
		server_scope.replace(starting_pos, closing_brace - starting_pos + 1, "");
	}
	server_scope.replace(0, server_scope.find("\n"), "");
	while (server_scope.find(";") != std::string::npos)
	{
		std::string line = server_scope.substr(skipWhitespaces(server_scope), server_scope.find(";") - skipWhitespaces(server_scope));
		std::list<std::string> element = splitString(line, " ");
		if (errorServer(element, &ret_server))
			throw ParsingException(0, element.front() + " not supported");
		server_scope.replace(0, server_scope.find(";") + 1, "");
	}
	checkServer(&ret_server);
	return (ret_server);
}

Config::location	Config::parseLocation(std::string location_scope)
{DEBUG("parseLocation")
	std::string element;
	size_t pos = 0;
	size_t start_name;
	Config::location retval;
	size_t location_len;

	element = location_scope.substr(pos, location_scope.find("{") - 1);
	if ((location_len = element.find(" ", 0)) == std::string::npos)
		throw ParsingException (0, "location badly defined."); // element.substr(location_len)
	start_name = location_len + skipWhitespaces(&element[location_len]);
	retval["name"] = std::list<std::string>(1, element.substr(start_name, std::string(&element[start_name]).find(" ")));
	location_scope.replace(pos, location_scope.find("{") + 1, "");
	while (location_scope.find(";") != std::string::npos)
	{
		element = location_scope.substr(skipWhitespaces(location_scope), location_scope.find(";") - skipWhitespaces(location_scope));
		std::list<std::string> tmp_list = splitString(element, " ");
		std::string name = tmp_list.front();
		tmp_list.pop_front();
		retval[name] = tmp_list;
		location_scope.replace(pos, location_scope.find(";") + 1, "");
	}
	checkLocation(retval);
	return (retval);
}

void	Config::checkServer(Config::server *retval)
{DEBUG("checkServer")
	if (retval->names.empty())
		retval->names.push_back("default");
	if (retval->host.empty())
		throw ParsingException(0, "Host has no name.");
	if (retval->port == 0)
			throw ParsingException(0, "Host has no port.");
	if (retval->root.empty())
		retval->root = "./default/default.html";
	int error_code[13] = {400, 403, 404, 405, 406, 411, 413, 500, 501, 502, 503, 504, 505};
	for (size_t i = 0; i < 13; i++)
	{
		std::ostringstream ss;
		ss << error_code[i];
		if (retval->error_pages[error_code[i]].empty())
			retval->error_pages[error_code[i]] = "./default/error_pages/error_" + ss.str() + ".html";
	}
}

void	Config::checkLocation(Config::location retval)
{DEBUG("checkLocation")
	for (Config::location::iterator i = retval.begin(); i != retval.end(); i++)
		if (std::find(location_values.begin(), location_values.end(), i->first) == location_values.end())
			throw ParsingException(0, i->first + " not a valid element");
}

std::list<Config::server>		&Config::getServers()
{
	return (this->servers);
}

Config::~Config()
{DEBUG("config destructor")
	std::map<std::string, location > locations;

	location_values.clear();
	for (std::list<server>::iterator it = servers.begin(); it != servers.end(); it++)
	{
		it->error_pages.clear();
		for (std::map<std::string, Config::location >::iterator it1 = it->locations.begin();
			it1 != it->locations.end(); it1++)
		{
			for (Config::location::iterator it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
				it2->second.clear();
			it1->second.clear();
		}
	}
	servers.clear();
}
