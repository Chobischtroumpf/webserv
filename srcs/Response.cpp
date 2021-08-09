#include "Response.hpp"

Response::Response()
{}

Response::Response(Response &Other)
{
	this->header = Other.getResponseHeaderObj();
}

Response::Response(HttpRequest request, Config::server server_config)
{
	//
}

