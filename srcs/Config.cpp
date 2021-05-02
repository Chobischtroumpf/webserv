#include "Config.hpp"

Config::Config(std::string file)
{
	std::string file_content = skip_comment(readFile(file));
	// si je trouve server alors bracket_management
	// if (file_content.find("server"))
	log_file(file_content);
}

void Config::bracket_management(std::string file)
{
	// this->servers || this->server->location = what you want
	size_t first;
	if ((first = file.find("{")) != std::string::npos)
	{
		size_t pos_open = file.find("{", first);
		size_t pos_close = file.find("}", first);
		if (pos_close == std::string::npos)
			throw ParsingException(0, "error in config file : unmatched bracket");
		if (pos_open != std::string::npos && pos_open < pos_close)
			this->bracket_management(std::string(file.c_str() + first));
	}
}


// serv {
//	location /bla/ {}
//}