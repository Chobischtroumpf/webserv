#include "Config.hpp"

// std::list<std::string> Config::populateLocationValue() 
// {DEBUG("populateLocationValue")
// 	std::list<std::string> ret;
// 	ret.push_back("name");
// 	ret.push_back("root");
// 	ret.push_back("method");
// 	ret.push_back("index");
// 	ret.push_back("upload_path");
// 	ret.push_back("autoindex");
// 	ret.push_back("upload_enable");
// 	ret.push_back("cgi_extension");
// 	ret.push_back("cgi_path");
// 	ret.push_back("client_max_body_size");
// 	return (ret);
// };

Config::Config(std::string file)
{
	DEBUG("##### CONFIG #####\n")
	if (file.compare(file.size() - 5, 5, ".conf") != 0)
		throw ParsingException(0, "Config file needs .conf extention");
	std::string file_content = skipComment(readFile(file));
	size_t starting_pos, pos = 0;
	Config::server serveur;
	// this->location_values = populateLocationValue();

	if(countChar('{', file_content) != countChar('}', file_content))
		throw ParsingException(0, "error in config file : unmatched bracket");
	while ((starting_pos = file_content.find("server", pos)) != std::string::npos)
	{
		pos = getScope(file_content, file_content.find("{", starting_pos));
		serveur = parseServer(file_content.substr(starting_pos, pos));
		logServConfig(serveur); //logging
		this->servers.push_back(serveur);
	}
}

size_t	Config::getScope(std::string file, size_t starting_pos)
{DEBUG("getScope")
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

Config::server	Config::parseServer(std::string server_scope)
{DEBUG("parseServer")
	size_t	starting_pos = 0;
	size_t	closing_brace;
	Config::server ret_server;
	Config::location tmp_location;
	ret_server.port = 0;
	while ((starting_pos = server_scope.find("location", starting_pos)) != std::string::npos)
	{
		closing_brace = getScope(server_scope, server_scope.find("{", starting_pos));
		tmp_location = parseLocation(server_scope.substr(starting_pos, closing_brace - starting_pos + 1));
		ret_server.locations[tmp_location.name] = tmp_location;
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
	retval.name = element.substr(start_name, std::string(&element[start_name]).find(" "));
	location_scope.replace(pos, location_scope.find("{") + 1, "");
	while (location_scope.find(";") != std::string::npos)
	{
		element = location_scope.substr(skipWhitespaces(location_scope), location_scope.find(";") - skipWhitespaces(location_scope));
		std::list<std::string> tmp_list = splitString(element, " ");
		std::string name = tmp_list.front();
		tmp_list.pop_front();
		if (name == "root")
			retval.root = tmp_list.front();
		else if (name == "method")
			retval.method = tmp_list;
		else if (name == "redirections")
			retval.redirections = tmp_list;
		else if (name == "index")
			retval.index = tmp_list.front();
		else if (name == "upload_path")
			retval.upload_path = tmp_list.front();
		else if (name == "autoindex")
			if (tmp_list.front() == "on")
				retval.is_autoindex = true;
			else
				retval.is_autoindex = false;
		else if (name == "upload_enable")
			if (tmp_list.front() == "on")
				retval.is_upload_enable = true;
			else
				retval.is_autoindex = false;
		else if (name == "upload_path")
			retval.upload_path = tmp_list.front();
		else if (name == "cgi_path")
			retval.upload_path = tmp_list.front();
		else if (name == "upload_path")
			retval.upload_path = tmp_list.front();
		location_scope.replace(pos, location_scope.find(";") + 1, "");
	}
	checkLocation(retval);
	return (retval);
}

std::list<Config::server>		&Config::getServers()
{
	return (this->servers);
}

Config::~Config()
{DEBUG("config destructor")
	std::map<std::string, location > locations;

	for (std::list<server>::iterator it = servers.begin(); it != servers.end(); it++)
	{
		it->error_pages.clear();
		for (std::map<std::string, Config::location>::iterator it1 = (it->locations).begin();
			it1 != it->locations.end(); it1++)
		{
			it1->second.method.clear();
			it1->second.redirections.clear();
		}
		it->locations.clear();
	}
	servers.clear();
}
