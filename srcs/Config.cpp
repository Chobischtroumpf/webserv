#include "Config.hpp"

Config::Config(std::string file)
{
	std::string file_content = skip_comment(readFile(file));
	size_t starting_pos;
	// size_t	after_server;
	std::vector<size_t> pos(2, 0);

	if(count_char('{', file_content) != count_char('}', file_content))
		throw ParsingException(0, "error in config file : unmatched bracket");
	// si je trouve server alors offset_cut_scope
	while((starting_pos = file_content.find("server", pos[1])) != std::string::npos)
	{
		// after_server = file_content.find("server", *(pos.end())) + 7;
		pos = offset_cut_scope(file_content, starting_pos);
		if ((file_content.find("}", pos[1] + 1) < file_content.find("{", pos[1] + 1)))
			throw ParsingException(0, "error in config file : closing bracket unmatched");
		{
			std::string server = file_content.substr(pos[0] + 1, pos[1] - pos[0] - 1);
			{
				
			}
		}
		// begin = skip_whitespaces(part);
		// end_tmp = skip_whitespaces(reverse_str(part));
		// part = part.substr(pos, end_tmp);
		std::cout << server << std::endl << std::endl;

	}
	// log_file(file_content);
}

std::vector<size_t> 	Config::offset_cut_scope(std::string file, size_t starting_pos)
{
	std::vector<size_t> pos(2, 0);

	pos[0] = file.find("{", starting_pos);
	pos[1] = file.find("}", starting_pos);
	if (pos[0] != std::string::npos && pos[0] < pos[1])
		pos = offset_cut_scope(file, pos[1] + 1);
	return (pos);
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