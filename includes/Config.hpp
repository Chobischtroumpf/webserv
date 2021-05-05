#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <string>
# include <iostream>
# include <sstream>
# include <list>
# include "General.hpp"
std::string readFile(std::string file);

class Config
{
	public:
		struct location
		{
			std::string				name;
			std::string				root;
			std::list<std::string>	method;
			std::string				index;
			std::string				upload_path;
			bool					is_autoindex;
			bool					is_upload_enable;
		};
		struct server
		{
			std::list<std::string> names;
			std::string host;
			std::string root;
			std::map<int, std::string> error_pages;
			std::map<std::string, location> locations;
			size_t port;
		};
	private:
		std::map<std::string, server> servers;
	public:
		Config(std::string file);
		void	parse_location(std::string location_scope);
		void	parse_server(std::string server_scope);
		size_t	offset_cut_scope(std::string files, size_t starting_pos);

};


#endif