#ifndef __OpenglGame__Exception__
#define __OpenglGame__Exception__

#include <string>
#include <exception>

class Exception: public std::exception
{
private:
	std::string _msg;
public:
	Exception(const std::string& msg):
	_msg(msg)
	{
	}

	virtual const char* what() const throw()
	{
		return _msg.c_str();
	}
};

#endif /* defined(__OpenglGame__Exception__) */
