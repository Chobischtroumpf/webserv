#include "Config.hpp"

std::list<std::string> Config::populate_location_value() 
{std::cout << "\033[0;35m\e[1mpopulate_location_value\e[0m\033[0m" << std::endl;
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
{std::cout << "\033[0;35m\e[1mConfig\e[0m\033[0m" << std::endl;
	if (file.compare(file.size() - 5, 5, ".conf") != 0)
		throw ParsingException(0, "Config file needs .conf extention");
	std::string file_content = skip_comment(readFile(file));
	size_t starting_pos, pos = 0;
	Config::server serveur;
	this->location_values = populate_location_value();

	if(count_char('{', file_content) != count_char('}', file_content))
		throw ParsingException(0, "error in config file : unmatched bracket");
	while ((starting_pos = file_content.find("server", pos)) != std::string::npos)
	{
		pos = offset_cut_scope(file_content, file_content.find("{", starting_pos));
		serveur = parse_server(file_content.substr(starting_pos, pos));
		log_serv_config(serveur);
		this->servers.push_back(serveur);
	}
}

size_t	Config::offset_cut_scope(std::string file, size_t starting_pos)
{std::cout << "\033[0;35m\e[1moffset_cut_scope\e[0m\033[0m" << std::endl;
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

bool	check_listen(std::list<std::string> element, Config::server *ret_serv)
{std::cout << "\033[0;35m\e[1mcheck_listen\e[0m\033[0m" << std::endl;
	if (element.front() == "listen")
	{
		if (element.size() != 3)
			throw ParsingException(0, "wrong amount of arguments to listen");
		element.pop_front();
		if (!(is_number(element.front()) && (ret_serv->port = std::atoi(element.front().c_str())) >=0))
			throw ParsingException(0, element.front() + " is not a valid port");
		element.pop_front();
		ret_serv->host = element.front();
		return (true);
	}
	else
		return (false);
}

bool	check_server_name(std::list<std::string> element, Config::server *ret_serv)
{std::cout << "\033[0;35m\e[1mcheck_server_name\e[0m\033[0m" << std::endl;
	if (element.front() == "server_name")
	{
		if (element.size() < 2)
			throw ParsingException(0, "not enough arguments in server_name");
		element.pop_front();
		ret_serv->names.insert(ret_serv->names.end(), element.begin(), element.end());
	}
	return (!ret_serv->names.empty());
}

bool	check_error_page(std::list<std::string> element, Config::server *ret_serv)
{std::cout << "\033[0;35m\e[1mcheck_error_page\e[0m\033[0m" << std::endl;
	ssize_t		tmp_err;
	if (element.front() == "error_page")
	{
		if (element.size() != 3)
			throw ParsingException(0, "wrong amount of arguments to error_page");
		tmp_err = -1;
		element.pop_front();
		if (!(is_number(element.front()) && (tmp_err = std::atoi(element.front().c_str())) >=0))
			throw ParsingException(0, element.front() + " is not a numeric value.");
		element.pop_front();
		ret_serv->error_pages[tmp_err] = element.front();
	}
	return (!ret_serv->error_pages.empty());
}

bool	check_root(std::list<std::string> element, Config::server *ret_serv)
{std::cout << "\033[0;35m\e[1mcheck_root\e[0m\033[0m" << std::endl;
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

bool	error_server(std::list<std::string> element, Config::server *ret_serv)
{std::cout << "\033[0;35m\e[1merror_server\e[0m\033[0m" << std::endl;
	return (!(check_listen(element, ret_serv)
		|| check_server_name(element, ret_serv)
		|| check_error_page(element, ret_serv)
		|| check_root(element, ret_serv)));
}

Config::server	Config::parse_server(std::string server_scope)
{std::cout << "\033[0;35m\e[1mparse_server\e[0m\033[0m" << std::endl;
	size_t	starting_pos = 0;
	size_t	closing_brace;
	Config::server ret_server;
	Config::location tmp_location;
	ret_server.port = 0;
	while ((starting_pos = server_scope.find("location", starting_pos)) != std::string::npos)
	{
		closing_brace = offset_cut_scope(server_scope, server_scope.find("{", starting_pos));
		tmp_location = parse_location(server_scope.substr(starting_pos, closing_brace - starting_pos + 1));
		ret_server.locations[tmp_location["name"].front()] = tmp_location;
		server_scope.replace(starting_pos, closing_brace - starting_pos + 1, "");
	}
	server_scope.replace(0, server_scope.find("\n"), "");
	while (server_scope.find(";") != std::string::npos)
	{
		std::string line = server_scope.substr(skip_whitespaces(server_scope), server_scope.find(";") - skip_whitespaces(server_scope));
		std::list<std::string> element = split_string(line, " ");
		if (error_server(element, &ret_server))
			throw ParsingException(0, element.front() + " not supported");
		server_scope.replace(0, server_scope.find(";") + 1, "");
	}
	check_server(&ret_server);
	return (ret_server);
}

Config::location	Config::parse_location(std::string location_scope)
{std::cout << "\033[0;35m\e[1mparse_location\e[0m\033[0m" << std::endl;
	std::string element;
	size_t pos = 0;
	size_t start_name;
	Config::location retval;
	size_t location_len;

	element = location_scope.substr(pos, location_scope.find("{") - 1);
	if ((location_len = element.find(" ", 0)) == std::string::npos)
		throw ParsingException (0, "location badly defined."); // element.substr(location_len)
	start_name = location_len + skip_whitespaces(&element[location_len]);
	retval["name"] = std::list<std::string>(1, element.substr(start_name, std::string(&element[start_name]).find(" ")));
	location_scope.replace(pos, location_scope.find("{") + 1, "");
	while (location_scope.find(";") != std::string::npos)
	{
		element = location_scope.substr(skip_whitespaces(location_scope), location_scope.find(";") - skip_whitespaces(location_scope));
		std::list<std::string> tmp_list = split_string(element, " ");
		std::string name = tmp_list.front();
		tmp_list.pop_front();
		retval[name] = tmp_list;
		location_scope.replace(pos, location_scope.find(";") + 1, "");
	}
	check_location(retval);
	return (retval);
}

void	Config::check_server(Config::server *retval)
{std::cout << "\033[0;35m\e[1mcheck_server\e[0m\033[0m" << std::endl;
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

void	Config::check_location(Config::location retval)
{std::cout << "\033[0;35m\e[1mcheck_location\e[0m\033[0m" << std::endl;
	for (Config::location::iterator i = retval.begin(); i != retval.end(); i++)
		if (std::find(location_values.begin(), location_values.end(), i->first) == location_values.end())
			throw ParsingException(0, i->first + " not a valid element");
}

std::list<Config::server>		Config::getServers()
{
	return (this->servers);
}

Config::~Config()
{
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
