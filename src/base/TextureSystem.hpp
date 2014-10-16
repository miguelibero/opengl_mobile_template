#ifndef __opengl_game__TextureSystem__
#define __opengl_game__TextureSystem__

#include <map>
#include <string>
#include <base/Gl.hpp>
#include <entityx/entityx.h>

class NativeBridge;

class TextureSystem : public entityx::System<TextureSystem>
{
    typedef std::map<std::string, GLuint> Textures;
    
    NativeBridge& _bridge;
    Textures _textures;

    GLuint getTexture(const std::string& name);
    
public:
    TextureSystem(NativeBridge& bridge);
    void update(entityx::EntityManager& es, entityx::EventManager& events, double dt);
};

#endif /* defined(__opengl_game__TextureSystem__) */
