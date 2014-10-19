#ifndef __opengl_game__ShaderSystem__
#define __opengl_game__ShaderSystem__

#include <map>
#include <string>
#include <entityx/entityx.h>
#include "base/Gl.hpp"

class NativeBridge;

class ShaderSystem : public entityx::System<ShaderSystem>
{
    typedef std::map<std::string, GLuint> Shaders;
    typedef std::map<std::pair<std::string,std::string>, GLuint> Programs;
    
    NativeBridge& _bridge;
    Shaders _shaders;
    Programs _programs;

    GLuint getShader(const std::string& name, GLenum type);
    GLuint getProgram(const std::string& vertex, const std::string& fragment);
    
public:
    ShaderSystem(NativeBridge& bridge);
    void update(entityx::EntityManager& es, entityx::EventManager& events, double dt);
};

#endif /* defined(__opengl_game__ShaderSystem__) */
