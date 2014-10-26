
#ifndef __OpenglGame__TransformComponent__
#define __OpenglGame__TransformComponent__

#include <entityx/entityx.h>
#include <glm/glm.hpp>

struct TransformComponent : public entityx::Component<TransformComponent>
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 transform;
    
    TransformComponent(const glm::vec3& position=glm::vec3(0.0f, 0.0f, 0.0f),
                       const glm::vec3& rotation=glm::vec3(0.0f, 0.0f, 0.0f),
                       const glm::vec3& scale=glm::vec3(1.0f, 1.0f, 1.0f)):
    position(position), rotation(rotation), scale(scale)
    {
    }
};

#endif /* defined(__OpenglGame__TransformComponent__) */