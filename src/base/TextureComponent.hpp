
#ifndef OpenglGame_TextureComponent_h
#define OpenglGame_TextureComponent_h

#include <entityx/entityx.h>
#include <base/Gl.hpp>

struct TextureComponent : public entityx::Component<TextureComponent>
{
    std::string name;
    GLuint texture;
    
    TextureComponent(const std::string& name, GLuint texture=0):
    name(name), texture(texture)
    {
    }
};


#endif
