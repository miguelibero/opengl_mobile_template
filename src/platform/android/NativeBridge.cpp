
#include "base/NativeBridge.hpp"
#include "platform/android/JniObject.hpp"
#include "base/Log.hpp"
#include "base/Exception.hpp"

JniObject getJniObject()
{
	static JniObject obj = JniObject::findSingleton("com.openglgame.NativeBridge");
	return obj;
}

NativeBridge::DataPtr NativeBridge::readFile(const std::string& name)
{
	try
	{
		auto data = new Data(getJniObject().call("readFile", Data(), name));
		return DataPtr(data);
	}
	catch(JniException e)
	{
		throw Exception(std::string("Error reading asset '")+name+"': "+e.what());
	}
}

NativeBridge::DataPtr NativeBridge::readImage(const std::string& name)
{
	try
	{
		auto data = new Data(getJniObject().call("readImage", Data(), name));
		return DataPtr(data);
	}
	catch(JniException e)
	{
		throw Exception(std::string("Error reading image '")+name+"': "+e.what());
	}
}
