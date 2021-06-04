#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

void throwError(const std::exception& ex);
std::string uIntegerToString(size_t n);

class ParsingException : public std::exception
{
	private:
		std::string _msg;
	public:
		ParsingException(int line = 0, std::string msg = "Unable to parse the given config file.")
		: _msg("Line: " + uIntegerToString(line + 1) + ": " + msg)
		{};
		~ParsingException() throw()
		{};
		const char *what () const throw ()
		{
			return (_msg.c_str());
		};
};

class ServerException : public std::exception
{
	private:
		std::string _msg;
	public:
		ServerException(std::string msg = "the server met an unrecoverable error.")
		: _msg(msg)
		{};
		~ServerException() throw()
		{};
		const char *what () const throw ()
		{
			return (_msg.c_str());
		};
};

class SubServException : public std::exception
{
	private:
		std::string _msg;
	public:
		SubServException(std::string msg = "the SubServer met an unrecoverable error.")
		: _msg(msg)
		{};
		~SubServException() throw()
		{};
		const char *what () const throw ()
		{
			return (_msg.c_str());
		};
};


#endif
