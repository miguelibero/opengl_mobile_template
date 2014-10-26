#ifndef __opengl_game__RenderSystem__
#define __opengl_game__RenderSystem__

#include <map>
#include <string>
#include <memory>
#include <entityx/entityx.h>
#include "base/Gl.hpp"
#include "base/ProgramDefinition.hpp"
#include "base/MaterialDefinition.hpp"

class NativeBridge;

class RenderSystem : public entityx::System<RenderSystem>
{
    typedef std::map<std::string, GLuint> Textures;
    typedef std::map<std::string, GLuint> Shaders;
    typedef std::map<std::string, std::shared_ptr<ProgramDefinition>> Programs;
    typedef std::map<std::string, std::shared_ptr<MaterialDefinition>> Materials;
    
    Textures _textures;
    Shaders _shaders;
    Programs _programs;
    Materials _materials;
    NativeBridge& _bridge;

    GLuint loadShader(const std::string& name, GLenum type);
    GLuint loadTexture(const std::string& name);    
    
public:
    RenderSystem(NativeBridge& bridge);
    void update(entityx::EntityManager& es, entityx::EventManager& events, double dt);

    void defineProgram(const std::string& name, const ProgramDefinition& definition);
    void defineMaterial(const std::string& name, const MaterialDefinition& definition);

    std::shared_ptr<ProgramDefinition> loadProgram(const std::string& name);
    std::shared_ptr<MaterialDefinition> loadMaterial(const std::string& name);
};

#endif /* defined(__opengl_game__RenderSystem__) */