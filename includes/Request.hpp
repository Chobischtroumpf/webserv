#ifndef REQUEST_HPP
#define REQUEST_HPP

#include "General.hpp"

class HttpRequest
{
	private:
		std::string							_method;				// GET, POST OR DELETE
		std::string							_version;				// Should always be "HTTP/1.1" of  "HTTP/1.0", otherwise -> Bad Request
		std::map<std::string, std::string>	_header_fields;			// < Key, Value>
		std::string							_header;				// Everything before CRLF 
		std::string							_body;					// Everything after CRLF 
		std::string							_raw;					// Whole request
		std::string							_path;					// Path to requested
		std::list<std::string>				_available_locations;	// locations from config file
		Config::location					_location;
		int									_return_code;			// initialized at 200, changed properly if an error occurs

	public:
		HttpRequest();
		HttpRequest(std::string req, Config::server conf);
		HttpRequest(const HttpRequest &other);
		~HttpRequest();
		
		HttpRequest& 						operator=(const HttpRequest &other);

		void								splitHeadBody();
		void								parseHeader();
		void								displayRequest();
		bool								validateRequest(Config::server serv_conf);

		std::string							getMethod() const;
		std::string							getVersion() const;
		std::map<std::string, std::string>&	getHeaderFields();
		std::string							getHeader() const;
		std::string							getBody() const;
		std::string							getRaw() const;
		std::string							getPath() const;
		int									getCode() const;

		bool								checkMethod();
		bool								checkVersion();
		bool								checkPath(Config::server serv_conf);
		bool								checkFile();
		void								makePath(Config::server serv_conf);

};

#endif