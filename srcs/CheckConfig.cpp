#include "Config.hpp"

bool	checkListen(std::list<std::string> element, Config::server *ret_serv)
{DEBUG("checkListen")
	if (element.front() == "listen")
	{
		if (element.size() != 3)
			throw ParsingException(0, "wrong amount of arguments to listen");
		element.pop_front();
		if (!(isNumber(element.front()) && (ret_serv->port = std::atoi(element.front().c_str())) >=0))
			throw ParsingException(0, element.front() + " is not a valid port");
		element.pop_front();
		ret_serv->host = element.front();
		return (true);
	}
	else
		return (false);
}

bool	checkServerName(std::list<std::string> element, Config::server *ret_serv)
{DEBUG("checkServerName")
	if (element.front() == "server_name")
	{
		if (element.size() < 2)
			throw ParsingException(0, "not enough arguments in server_name");
		element.pop_front();
		ret_serv->names.insert(ret_serv->names.end(), element.begin(), element.end());
	}
	return (!ret_serv->names.empty());
}

bool	checkErrorPage(std::list<std::string> element, Config::server *ret_serv)
{DEBUG("checkErrorPage")
	ssize_t		tmp_err;
	if (element.front() == "error_page")
	{
		if (element.size() != 3)
			throw ParsingException(0, "wrong amount of arguments to error_page");
		tmp_err = -1;
		element.pop_front();
		if (!(isNumber(element.front()) && (tmp_err = std::atoi(element.front().c_str())) >=0))
			throw ParsingException(0, element.front() + " is not a numeric value.");
		element.pop_front();
		ret_serv->error_pages[tmp_err] = element.front();
	}
	return (!ret_serv->error_pages.empty());
}

bool	checkRoot(std::list<std::string> element, Config::server *ret_serv)
{DEBUG("checkRoot")
	if (element.front() == "root")
	{
		if (element.size() != 2)
			throw ParsingException(0, "wrong amount of arguments to root");
		element.pop_front();
		if (*(element.front().begin()) == '/')
			ret_serv->root = element.front();
	}
	return (!ret_serv->root.empty());
}

bool	errorServer(std::list<std::string> element, Config::server *ret_serv)
{DEBUG("errorServer")
	return (!(checkListen(element, ret_serv)
		|| checkServerName(element, ret_serv)
		|| checkErrorPage(element, ret_serv)
		|| checkRoot(element, ret_serv)));
}

void	Config::checkServer(Config::server *retval)
{DEBUG("checkServer")
	if (retval->names.empty())
		retval->names.push_back("default");
	if (retval->host.empty())
		throw ParsingException(0, "Host has no name.");
	if (retval->port == 0)
			throw ParsingException(0, "Host has no port.");
	if (retval->root.empty())
		retval->root = "./default/default.html";
	int error_code[13] = {400, 403, 404, 405, 406, 411, 413, 500, 501, 502, 503, 504, 505};
	for (size_t i = 0; i < 13; i++)
	{
		std::ostringstream ss;
		ss << error_code[i];
		if (retval->error_pages[error_code[i]].empty())
			retval->error_pages[error_code[i]] = "./default/error_pages/error_" + ss.str() + ".html";
	}
}

void	Config::checkLocation(Config::location retval)
{DEBUG("checkLocation")
	if (retval.name.empty())
		throw ParsingException(0,"missing location name");
	if (retval.root.empty())
		throw ParsingException(0,"missing root directory for location");
	if (retval.index.empty())
		retval.index = "./index.html";
	if (retval.method.empty())
	{
		retval.method.push_back("GET");
		retval.method.push_back("PUSH");
		retval.method.push_back("DELETE");
	}
	if (retval.is_upload_enable && retval.upload_path.empty())
		retval.upload_path = "./";
	if (retval.cgi_extension.empty())
		retval.cgi_extension = "php";
	if (retval.cgi_path.empty())
		retval.cgi_path = "/usr/bin/";

}