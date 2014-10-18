
#include "base/NativeBridge.hpp"
#include "platform/android/JniObject.hpp"
#include "base/Log.hpp"

JniObject getJniObject()
{
	static JniObject obj = JniObject::findSingleton("com.openglgame.NativeBridge");
	return obj;
}

NativeBridge::DataPtr NativeBridge::readAsset(const std::string& name)
{
	auto data = new Data(getJniObject().call("readAsset", Data(), name));
	if(getJniObject().hasError())
	{
		throw NativeException(std::string("Error reading asset '")+name+"'.");
	}
    return DataPtr(data);
}

NativeBridge::DataPtr NativeBridge::readImage(const std::string& name)
{
	auto data = new Data(getJniObject().call("readImage", Data(), name));
	if(getJniObject().hasError())
	{
		throw NativeException(std::string("Error reading image '")+name+"'.");
	}
	LogDebug("Loaded image '%s' of size %zu", name.c_str(), data->size());
    return DataPtr(data);
}
