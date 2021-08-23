#ifndef CONFIG_HPP
# define CONFIG_HPP

# include <map>
# include <string>
# include <iostream>
# include <sstream>
# include <unistd.h>
# include <list>
# include <algorithm>

int readFile(std::string file, std::string *content);

class Config
{
	public:
		struct location {
			std::string					name;
			std::string					root;
			std::list<std::string>		method;
			std::list<std::string>		redirections;
			std::string					index;
			std::string					upload_path;
			bool						is_autoindex;
			bool						is_upload_enable;
			std::string					cgi_extension;
			std::string					cgi_path;
			std::string					max_body_size;
			/*! @brief overload of operator = */
			struct location& operator=(location const &copied){
				this->name = copied.name;
				this->root = copied.root;
				this->method = copied.method;
				this->redirections = copied.redirections;
				this->index = copied.index;
				this->upload_path = copied.upload_path;
				this->is_autoindex = copied.is_autoindex;
				this->is_upload_enable = copied.is_upload_enable;
				this->cgi_extension = copied.cgi_extension;
				this->cgi_path = copied.cgi_path;
				this->max_body_size = copied.max_body_size;
				return (*this);
			}
		};
		struct server
		{
			std::list<std::string> names;
			std::string host;
			std::string root;
			std::map<int, std::string> error_pages;
			std::map<std::string, struct location> locations;
			size_t port;
			/*! @brief overload of operator = */
			struct server& operator=(server const &copied){
				this->names = copied.names;
				this->root = copied.root;
				this->host = copied.host;
				this->error_pages = copied.error_pages;
				this->locations = copied.locations;
				this->port = copied.port;
				return (*this);
			}
		};
		
	private:
		// std::list<std::string> location_values;
		std::list<server> servers;
	public:
		/*! @brief Constructor : -> takes a .conf file as string
								 -> checks extension
								 -> strips down comments
								 -> checks format
								 -> add each subserv to a list (servers)
		*/
		Config(std::string file);

		/*! @brief	-> receives a portion of .conf file corresponding to a subserver
					-> finds 'location' portion(s)
					-> parse the other elements of the subserver
					-> checks information validity with 'errorServer' and 'checkServer' functions
		*/
		struct server			parseServer(std::string server_scope);

		/*! @brief	-> receives a portion of .conf file corresponding to a location
					-> parse the elements
					-> checks information validity with 'checkLocation' function
		*/
		struct location			parseLocation(std::string location_scope);
		size_t					getScope(std::string files, size_t starting_pos);
		void					checkLocation(location retval);
		void					checkServer(Config::server *retval);
		std::list<std::string>	populateLocationValue();
		std::list<server>		&getServers();
		
		~Config();
};

bool	checkRoot(std::list<std::string> element, Config::server *ret_serv);
bool	checkErrorPage(std::list<std::string> element, Config::server *ret_serv);
bool	checkServerName(std::list<std::string> element, Config::server *ret_serv);
bool	checkListen(std::list<std::string> element, Config::server *ret_serv);
bool	errorServer(std::list<std::string> element, Config::server *ret_serv);

# include "General.hpp"
#endif
