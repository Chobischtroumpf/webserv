#include "Response.hpp"

Response::Response()
{}

Response::Response(Response &Other)
{
	this->header = Other.getResponseHeaderObj();
}

Response::Response(HttpRequest request, Config::server server_config)
{
	std::map<std::string, std::string> headers = request.GetHeaderFields();
	// check httpRequest for method
	std::string method = request.GetMethod();

	if (method == "GET")
		getMethod(request, server_config);
	else if (method == "POST")
		postMethod(request, server_config);
	else if (method == "DELETE")
		deleteMethod(request, server_config);
}

