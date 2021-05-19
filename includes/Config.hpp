#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <map>
# include <string>
# include <iostream>
# include <sstream>
# include <unistd.h>
# include <list>
# include <algorithm>

std::string readFile(std::string file);

class Config
{
	typedef	std::map<std::string, std::list<std::string> > location;
	public:
		// {
		// 	std::string					name;
		// 	std::string					root;
		// 	std::list<std::string>		method;
		// 	std::string					index;
		// 	std::string					upload_path;
		// 	bool						is_autoindex;
		// 	bool						is_upload_enable;
		// 	std::list<std::string>		cgi_extension;
		// 	std::string					cgi_path;
		// };
		struct server
		{
			std::list<std::string> names;
			std::string host;
			std::string root;
			std::map<int, std::string> error_pages;
			std::map<std::string, std::map<std::string, std::list<std::string> > > locations;
			size_t port;
		};
		
	private:
		std::list<std::string> location_values;
		std::list<server> servers;
	public:
		Config(std::string file);
		location				parse_location(std::string location_scope);
		server					parse_server(std::string server_scope);
		size_t					offset_cut_scope(std::string files, size_t starting_pos);
		void					check_location(location retval);
		void					check_server(Config::server *retval);
		std::list<std::string>	populate_location_value();
};

# include "General.hpp"
#endif