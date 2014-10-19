#include "base/ShaderSystem.hpp"
#include "base/NativeBridge.hpp"
#include "base/ShaderComponent.hpp"
#include "base/Log.hpp"
#include "base/Exception.hpp"

ShaderSystem::ShaderSystem(NativeBridge& bridge):
_bridge(bridge)
{
}

GLuint ShaderSystem::getShader(const std::string &name, GLenum type)
{
    std::string typeName(name);
    if(type == GL_VERTEX_SHADER)
    {
        typeName += ".vsh";
    }
    else if(type == GL_FRAGMENT_SHADER)
    {
        typeName += ".fsh";
    }
    auto itr = _shaders.find(typeName);
    if(itr != _shaders.end())
    {
        return itr->second;
    }
    auto data = _bridge.readFile(std::string("shaders/")+typeName);
    const GLchar* ptr = (const GLchar*) data->data();
    if(ptr == nullptr)
    {
        throw Exception(std::string("Could not read data for shader '")+typeName+"'.");
    }
    LogDebug("compiling shader '%s': %s", typeName.c_str(), ptr);
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &ptr, NULL);
    glCompileShader(shader);
    LogDebug("compiled shader '%s' into %d", typeName.c_str(), shader);
    _shaders[typeName] = shader;
    return shader;
}

GLuint ShaderSystem::getProgram(const std::string& vertex, const std::string& fragment)
{
    auto key = std::make_pair(vertex, fragment);
    auto itr = _programs.find(key);
    if(itr != _programs.end())
    {
        return itr->second;
    }
    GLuint vertexId = getShader(vertex, GL_VERTEX_SHADER);
    GLuint fragmentId = getShader(fragment, GL_FRAGMENT_SHADER);
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexId);
    glAttachShader(program, fragmentId);
    glLinkProgram(program);
    LogDebug("linked vertex '%s' and fragment '%s' into program %d", vertex.c_str(), fragment.c_str(), program);
    _programs[key] = program;
    return program;
}

void ShaderSystem::update(entityx::EntityManager& es, entityx::EventManager& events, double dt)
{
    ShaderComponent::Handle shader;
    for (entityx::Entity entity : es.entities_with_components(shader))
    {
        if(shader->program == 0)
        {
            try
            {
                shader->program = getProgram(shader->vertex, shader->fragment);
            }
            catch(Exception e)
            {
                LogDebug("ShaderSystem: %s", e.what());
                shader->program = -1;
            }
        }
    }
}
