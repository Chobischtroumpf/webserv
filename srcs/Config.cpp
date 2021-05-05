#include "Config.hpp"

Config::Config(std::string file)
{
	std::string file_content = skip_comment(readFile(file));
	size_t starting_pos;
	size_t pos = 0;
	if(count_char('{', file_content) != count_char('}', file_content))
		throw ParsingException(0, "error in config file : unmatched bracket");
	while ((starting_pos = file_content.find("server", pos)) != std::string::npos)
	{
		pos = offset_cut_scope(file_content, file_content.find("{", starting_pos));
		parse_server(file_content.substr(starting_pos, pos));
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


void	Config::parse_server(std::string server_scope)
{
	size_t	starting_pos = 0;
	size_t	closing_brace;
	while ((starting_pos = server_scope.find("location", starting_pos)) != std::string::npos)
	{
		closing_brace = offset_cut_scope(server_scope, server_scope.find("{", starting_pos));
		parse_location(server_scope.substr(starting_pos, closing_brace - starting_pos + 1));
		server_scope.replace(starting_pos, closing_brace - starting_pos + 1, "");
	}
}

void	Config::parse_location(std::string location_scope)
{
	std::cerr << location_scope << std::endl;
	std::list<std::string>	elements;
}

size_t	skip_whitespaces(std::string str)
{
	int i = -1;
	while (str[++i])
		if (!isspace(str[i]))
			break;
	return (i);
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