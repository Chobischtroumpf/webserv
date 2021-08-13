#ifndef RESPONSEHEADER_HPP
# define RESPONSEHEADER_HPP
# include "General.hpp"

class	ResponseHeader
{
	private:
		std::string					content_language;
		std::string					content_length;
		std::string					content_location;
		std::string					content_type;
		std::string					date;
		std::string					location;
		std::string					server;
		std::string					transfer_encoding;
		std::map<int, std::string>	errors;
		void						initErrorMap();
	public:
		ResponseHeader(void);
		ResponseHeader(ResponseHeader &Other);
		~ResponseHeader(void);
		
		ResponseHeader &operator=(const ResponseHeader &src);

		std::string	setErrorCode(int code, Config::server server_config);
		void		setContentLanguage(const std::string& lang = "");
		void		setContentLength(size_t size);
		void		setContentLocation(int code, const std::string& path = "");
		void		setContentType(std::string type, std::string path);
		void		setDate(void);
		void		setLocation(int code, const std::string&redirect);
		void		setServer(void);
		void		setTransferEncoding(void);

		std::string	getHeader(void);
		std::string	getContentLanguage(void);
		std::string	getContentLength(void);
		std::string	getContentLocation(void);
		std::string	getContentType(void);
		std::string	getDate(void);
		std::string	getLocation(void);
		std::string	getServer(void);
		std::string	getTransferEncoding(void);
		std::map<int, std::string>	getErrors(void);


		std::string	writeHeader(void);
		void		setValues(size_t size, const std::string& path, int code, std::string type, const std::string& content_location, const std::string& lang);
		std::string	getStatusMessage(int code);
};

#endif
