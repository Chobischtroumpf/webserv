#include "ResponseHeader.hpp"

ResponseHeader::ResponseHeader()
{
}

void	ResponseHeader::initErrorMap()
{
	errors[100]= "Continue";
	errors[200]= "OK";
	errors[201]= "Created";
	errors[100]= "No Content";
	errors[100]= "Bad Request";
	errors[100]= "Forbidden";
}
