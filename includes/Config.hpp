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
		//struct location {
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
		/* PARSE LOCATION */
		location				parseLocation(std::string location_scope);
		server					parseServer(std::string server_scope);
		size_t					offsetCutScope(std::string files, size_t starting_pos);
		void					checkLocation(location retval);
		void					checkServer(Config::server *retval);
		std::list<std::string>	populateLocationValue();
		std::list<server>		&getServers();
		~Config();
};

# include "General.hpp"
#endif
