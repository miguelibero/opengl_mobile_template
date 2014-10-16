
#ifndef __OpenglGame__TransformComponent__
#define __OpenglGame__TransformComponent__

#include <entityx/entityx.h>
#include <glm/glm.hpp>

struct TransformComponent : public entityx::Component<TransformComponent>
{
    glm::vec2 position;
    glm::vec2 rotation;
    glm::vec2 scale;
    glm::mat3 transform;
    
    TransformComponent(const glm::vec2& position=glm::vec2(0.0f, 0.0f),
                       const glm::vec2& rotation=glm::vec2(0.0f, 0.0f),
                       const glm::vec2& scale=glm::vec2(1.0f, 1.0f)):
    position(position), rotation(rotation), scale(scale)
    {
    }
};

#endif /* defined(__OpenglGame__TransformComponent__) */