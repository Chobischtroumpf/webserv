#include "General.hpp"


void getMethod()
{}

void parseHeaderFields()
{}

void validHeaderFormat()
{
	// Http version 1.1 ?
	// GET, POST or DEL Method
	// no empty lines
	// all the fields are valid fields -> check in a list of authorized fields
}

void request_parser(std::string request)
{
	// separate header and body
	// check validity of header
	// parse fields into struct
	// once completed, if everything went well -> parse body
}