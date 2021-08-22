#ifndef RESPONSEHEADER_HPP
# define RESPONSEHEADER_HPP

# include "General.hpp"
# include "Request.hpp"

class	ResponseHeader
{
	private:
		int							_status_code;
		std::string					_http_version;
		std::string					_content_language;
		int							_content_length;
		std::string					_content_location;
		std::string					_content_type;
		std::string					_date;
		std::string					_location;
		std::string					_server;
		std::string					_transfer_encoding;
		std::map<int, std::string>	_errors;
		void						initErrorMap();
	public:
		ResponseHeader();
		ResponseHeader(Request &request);
		ResponseHeader(ResponseHeader &Other);
		~ResponseHeader(void){};
		
		ResponseHeader &operator=(const ResponseHeader &src);

		void		setErrorCode(int code);
		void		setContentLanguage(const std::string& lang = "");
		void		setContentLength(size_t size);
		void		setContentLocation(int code, const std::string& path = "");
		void		setContentType(std::string type, std::string path);
		void		setDate(std::string date);
		void		setLocation(int code, const std::string&redirect);
		void		setServer(void);
		void		setVersion(std::string version);
		void		setTransferEncoding(void);

		std::string	getHeader(void);
		std::string	getContentLanguage(void) const;
		int getContentLength(void) const;
		std::string	getContentLocation(void) const;
		std::string	getContentType(void) const;
		std::string	getDate(void) const;
		int			getReturnCode(void) const;
		std::string	getLocation(void) const;
		std::string	getServer(void) const;
		std::string	getTransferEncoding(void) const;
		std::string	getVersion(void) const;
		std::map<int, std::string>	getErrors(void) const;

		void		generate_datetime(void);
		std::string	writeHeader(void);
		void		setValues(size_t size, const std::string& path, int code, std::string type, const std::string& content_location, const std::string& lang);
		std::string	getStatusMessage(int code);
};

#endif