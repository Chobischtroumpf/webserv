#include "Config.hpp"

Config::Config(std::string file)
{
	std::string file_content = skip_comment(readFile(file));
	size_t starting_pos, pos = 0;
	Config::server serveur;

	if(count_char('{', file_content) != count_char('}', file_content))
		throw ParsingException(0, "error in config file : unmatched bracket");
	while ((starting_pos = file_content.find("server", pos)) != std::string::npos)
	{
		pos = offset_cut_scope(file_content, file_content.find("{", starting_pos));
		serveur = parse_server(file_content.substr(starting_pos, pos));
		this->servers.push_back(serveur);
	}
}

size_t	Config::offset_cut_scope(std::string file, size_t starting_pos)
{
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


Config::server	Config::parse_server(std::string server_scope)
{
	size_t	starting_pos = 0;
	size_t	closing_brace;
	Config::server ret_server;
	Config::location tmp_location;
	while ((starting_pos = server_scope.find("location", starting_pos)) != std::string::npos)
	{
		closing_brace = offset_cut_scope(server_scope, server_scope.find("{", starting_pos));
		tmp_location = parse_location(server_scope.substr(starting_pos, closing_brace - starting_pos + 1));
		ret_server.locations[tmp_location["name"].front()] = tmp_location;
		server_scope.replace(starting_pos, closing_brace - starting_pos + 1, "");
	}
	return (ret_server);
}

Config::location	Config::parse_location(std::string location_scope)
{
	std::string element;
	size_t pos = 0;
	size_t start_name;
	Config::location retval;
	size_t location_len;
	// {
	//   map_name[location_name][sub_name]([pos]||iteration)
	// }
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
	for (location::iterator i = retval.begin(); i != retval.end(); i++)
	{
		std::clog << "\033[34;1m[" << i->first << " :]\033[0m" << std::endl;
		for (std::list<std::string>::iterator j = i->second.begin(); j != i->second.end(); j++)
			std::clog << "\t - \033[32;1m[" <<*j << "]\033[0m" << std::endl;
	}
//check

	return (retval);
}

// if (server)
// 		{
// 			// std::string content = file.substr(first, pos_open < pos_close ? pos_open : pos_close);
// 			{
// 				Config::server fields;
// 				size_t end_tmp;
// 				//host port root && location
// 				for (size_t pos = first; (end_tmp = file.find(";", pos)); pos = file.find(";", pos) + 1)
// 				{
// 					if (file.find("location", pos) < end_tmp)
// 						pos = this->offset_cut_scope(std::string(file.c_str() + pos_open), false);
// 					std::string part = file.substr(pos, end_tmp - 1);
// 					pos = skip_whitespaces(part);
// 					end_tmp = skip_whitespaces(reverse_str(part));
// 					part = part.substr(pos, end_tmp);
// 					if (part.find(" ") == std::string::npos)
// 						throw ParsingException(0, "config file badly formatted");
// 					fields[part.substr(pos, part.find(" "))] = part.substr(part.find(" "), end_tmp);
// 				}
// 				return (fields);
// 			}
// 		}
// 		else//location
// 		{
// 			std::map<std::string, Config::location> fields_location;
// 		}
		// begin = skip_whitespaces(part);
		// end_tmp = skip_whitespaces(reverse_str(part));
		// part = part.substr(pos, end_tmp);

// serv1 : 
// 	- 1
// 	- 2
// 	- 3
// 	- location:
// 		- 1
// 		- 2
// 		- 3	
// 	- location2:
//		- 1
//		- 2
//		- 3
// serv2 :
// 	- 1
// 	- 2
// 	- 3
// 	location:
// 		- 1
// 		- 2
// 		- 3

// serv {
//	location /bla/ {}
//}