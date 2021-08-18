#include "Response.hpp"

Response::Response()
{}

Response::Response(Response &Other)
{
	this->header = Other.getResponseHeaderObj();
}

std::string			Response::getErrorFile(int code ,Config::server server_config)
{
	(void) code;
	(void) server_config;
	std::string ret = std::string("Temporary error handling");
	return (ret);
}

std::string	Response::setErrorCode(Config::server server_config)
{
	std::string string = "";
	switch (error_code)
	{
		case 400:
			return(getErrorFile(400, server_config));
		case 403:
			return(getErrorFile(403, server_config));
		case 404:
			return(getErrorFile(404, server_config));
		case 405:
			return(getErrorFile(405, server_config));
		case 413:
			return(getErrorFile(413, server_config));
		default:
			break;
	}
	return (string);
}

Response::Response(Request request)
{
	// std::map<std::string, std::string> headers = request.GetHeaderFields();
	// check Request for method
	Config::server server_config = request.getConf();
	std::string method = request.getMethod();
	error_code = request.getCode();
	
	if ((this->response_body = setErrorCode(server_config)) == "")
	{
		if (method == "GET")
			getMethod(request, server_config);
		else if (method == "POST")
			postMethod(request, server_config);
		else if (method == "DELETE")
			deleteMethod(request, server_config);
	}
	
}

void Response::generate_datetime(void)
{
	std::time_t t = std::time(0);   // get time now
   	tm *ltm = localtime(&t);
	char buffer[80];
	// print various components of tm structure.
	//   std::cout << "Year:" << 1900 + ltm->tm_year << std::endl;
	//   std::cout << "Month: "<< 1 + ltm->tm_mon<< std::endl;
	//   std::cout << "Day: "<< ltm->tm_mday << std::endl;
	//   std::cout << "Time: "<< 5+ltm->tm_hour << ":";
	//   std::cout << 30+ltm->tm_min << ":";
	
	//   std::cout << ltm->tm_sec << std::endl;
		strftime (buffer,80,"Now it's %I:%M%p.",ltm);
  	std::cout << buffer;
}


std::string Response::getResponse(void)
{
	return (response_header + response_body);
}

std::string Response::getResponseBody(void)
{
	return (response_body);
}

std::string Response::getResponseHeader(void)
{
	return (response_header);
}

ResponseHeader	&Response::getResponseHeaderObj(void)
{
	return (header);
}

void	Response::getMethod(Request request, Config::server &server_config)
{
	(void)request;
	(void)server_config;
}
void	Response::postMethod(Request request, Config::server &server_config)
{
	(void)request;
	(void)server_config;
}
void	Response::deleteMethod(Request request, Config::server &server_config)
{
	(void)request;
	(void)server_config;
}
