#include "General.hpp"

class HttpRequest
{
	private:
		std::string							_method;		// GET, POST OR DELETE
		std::string							_version;		// Should always be "HTTP/1.1" of  "HTTP/1.0", otherwise -> Bad Request
		std::map<std::string, std::string>	_headers;		// < Key, Value>
		std::string							_body;			// Everything that is after a CRLF 
		std::string							_raw;			// Whole request
		std::string							_path;			// Path to requested 

	public:
		HttpRequest();
		HttpRequest(std::string req);
		HttpRequest(const HttpRequest &other);
		~HttpRequest();
		
		HttpRequest& 						operator=(const HttpRequest &other);

		void								ParseMethodVersion();
		void								ParseHeader();
		void								ParseBody();

		std::string							GetMethod() const;
		std::string							GetVersion() const;
		std::map<std::string, std::string>	GetHeaders() const;
		std::string							GetBody() const;
		std::string							GetRaw() const;
		
};