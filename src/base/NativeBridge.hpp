#ifndef __OpenglGame__NativeBridge__
#define __OpenglGame__NativeBridge__

#include <memory>
#include <vector>
#include <string>

class NativeBridge
{
public:
    
    typedef std::vector<uint8_t> Data;
    typedef std::unique_ptr<Data> DataPtr;
    
    DataPtr readAsset(const std::string& name);
    DataPtr readImage(const std::string& name);
};

#endif /* defined(__OpenglGame__NativeBridge__) */
