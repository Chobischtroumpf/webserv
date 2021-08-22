#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "General.hpp"
#include "Config.hpp"
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
		std::list<std::string>				_available_locations;	// locations from config file
		Config::location					_location;
		Config::server 						_conf;
		int									_status_code;			// initialized at 200, changed properly if an error occurs

	public:
		Request();
		Request(std::string req, Config::server conf);
		Request(const Request &other);
		~Request();
		
		Request& 						operator=(const Request &other);

		void								splitHeadBody();
		void								parseHeader();
		void								displayRequest();
		bool								validateRequest(Config::server serv_conf);
		void								initRequest();


		std::string							getMethod() const;
		std::string							getVersion() const;
		std::map<std::string, std::string>	getHeaderFields() const;
		std::string							getHeader() const;
		std::string							getBody() const;
		std::string							getRaw() const;
		std::string							getPath() const;
		int									getCode() const;
		Config::server						getConf() const;

		bool								checkMethod();
		bool								checkVersion();
		bool								checkPath(Config::server serv_conf);
		bool								checkFile();
		void								makePath(Config::server serv_conf);

};

#endif