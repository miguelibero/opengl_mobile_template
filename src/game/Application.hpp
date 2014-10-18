
#ifndef __OpenglGame__Application__
#define __OpenglGame__Application__

#include <entityx/entityx.h>
#include "base/NativeBridge.hpp"

class Application : public entityx::EntityX
{
private:
	NativeBridge _bridge;
public:
    Application();
    void load();
    void unload();
    void update(double dt);
};

#endif /* defined(__OpenglGame__Application__) */