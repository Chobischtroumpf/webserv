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
		int									_return_code;			// initialized at 200, changed properly if an error occurs

	public:
		HttpRequest();
		HttpRequest(std::string req, Config::server conf);
		HttpRequest(const HttpRequest &other);
		~HttpRequest();
		
		HttpRequest& 						operator=(const HttpRequest &other);

		void								SplitHeadBody();
		void								ParseHeader();
		void								DisplayRequest();
		bool								ValidateRequest();

		std::string							GetMethod() const;
		std::string							GetVersion() const;
		std::map<std::string, std::string>&	GetHeaderFields();
		std::string							GetHeader() const;
		std::string							GetBody() const;
		std::string							GetRaw() const;
		std::string							GetPath() const;

		bool								CheckMethod();
		bool								CheckVersion();
		bool								CheckPath();
};