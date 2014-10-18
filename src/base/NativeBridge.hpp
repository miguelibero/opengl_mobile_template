#ifndef __OpenglGame__NativeBridge__
#define __OpenglGame__NativeBridge__

#include <memory>
#include <vector>
#include <string>
#include <exception>

class NativeException: public std::exception
{
private:
	std::string _msg;
public:
	NativeException(const std::string& msg):
	_msg(msg)
	{
	}

	virtual const char* what() const throw()
	{
		return _msg.c_str();
	}
};

class NativeBridge
{
public:
    
    typedef std::vector<uint8_t> Data;
    typedef std::unique_ptr<Data> DataPtr;
    
    DataPtr readAsset(const std::string& name);
    DataPtr readImage(const std::string& name);
};

#endif /* defined(__OpenglGame__NativeBridge__) */
