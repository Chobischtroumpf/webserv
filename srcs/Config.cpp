#include "Config.hpp"

Config::Config(std::string file)
{
	std::string file_content = skip_comment(readFile(file));
	size_t starting_pos;
	// size_t	after_server;
	std::vector<size_t> pos(2, 0);
	// si je trouve server alors bracket_management
	while((starting_pos = file_content.find("server", pos[1])) != std::string::npos)
	{
		// after_server = file_content.find("server", *(pos.end())) + 7;
		pos = bracket_management(file_content, starting_pos);
		std::cout << pos[0] << " " << pos[1] << std::endl;
		// on fait notre
	}
	// log_file(file_content);
}

size_t	skip_whitespaces(std::string str)
{
	int i = -1;
	while (str[++i])
		if (!isspace(str[i]))
			break;
	return (i);
}

std::vector<size_t> 	Config::bracket_management(std::string file, size_t starting_pos)
{
	size_t pos_open;
	size_t pos_close = 0;
	std::vector<size_t> pos(2, 0);

	pos_open = file.find("{", starting_pos);
	pos_close = file.find("}", starting_pos);
	if (pos_close == std::string::npos)
		throw ParsingException(0, "error in config file : unmatched bracket");
	if (pos_open != std::string::npos && pos_open < pos_close)
		pos_close = bracket_management(file, pos_close + 1)[1];
	if (pos_close == std::string::npos)
		throw ParsingException(0, "error in config file : unmatched bracket");
	pos[0] = pos_open;
	pos[1] = pos_close;
	return (pos);
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
// 						pos = this->bracket_management(std::string(file.c_str() + pos_open), false);
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