#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "General.hpp"
#include "Config.hpp"
//#include "response.hpp"
class Request
{
	private:
		std::string							_method;				// GET, POST OR DELETE
		std::string							_version;				// Should always be "/1.1" of  "/1.0", otherwise -> Bad Request
		std::map<std::string, std::string>	_header_fields;			// < Key, Value>
		std::string							_header;				// Everything before CRLF 
		std::string							_body;					// Everything after CRLF 
		std::string							_raw;					// Whole request
		std::string							_path;					// Path to requested
		std::string							_path_on_machine;		// Path for machine to requested
		std::list<std::string>				_available_locations;	// locations from config file
		Config::location					_location;
		Config::server 						_conf;

		int									_status_code;			// initialized at 200, changed properly if an error occurs

	public:
		Request();
		Request(std::string req, Config::server &conf);
		Request(const Request &other);
		~Request();
		
		Request& 									operator=(const Request &other);

		void										splitHeadBody();
		void										parseHeader();
		void										displayRequest();
		bool										validateRequest(Config::server &serv_conf);
		void										initRequest();


		std::string	const							&getMethod() const;
		std::string	const							&getVersion() const;
		std::map<std::string, std::string> const	&getHeaderFields() const;
		std::string const							&getHeader() const;
		std::string const							&getBody() const;
		std::string const							&getRaw() const;
		std::string const							&getPath() const;
		std::string const							&getPathOnMachine() const;
		Config::server const						&getConf() const;
		std::string const							&getRedirection() const;
		std::list<std::string> const				&getAvailableLocations() const;	// locations from config file

		int											getRedirectionCode() const;
		int											getCode() const;
		bool 										getAutoIndex() const;
		bool 										hasRedirection() const;

		bool										checkMethod();
		bool										checkVersion();
		bool										checkPath(Config::server &serv_conf);
		bool										checkFile();
		void										checkAutoIndex();
		bool										checkSize();
		void										makePathOnMachine();

};

#endif