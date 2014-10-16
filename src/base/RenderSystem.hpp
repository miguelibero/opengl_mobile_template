
#ifndef __OpenglGame__RenderSystem__
#define __OpenglGame__RenderSystem__

#include <entityx/entityx.h>

class RenderSystem : public entityx::System<RenderSystem>
{
public:
    RenderSystem();
    void update(entityx::EntityManager& es, entityx::EventManager& events, double dt);
};

#endif /* defined(__OpenglGame__RenderSystem__) */
