#include "base/RenderSystem.hpp"
#include "base/NativeBridge.hpp"
#include "base/MaterialComponent.hpp"
#include "base/MeshComponent.hpp"
#include "base/Log.hpp"
#include "base/Exception.hpp"

RenderSystem::RenderSystem(NativeBridge& bridge):
_bridge(bridge)
{
}

GLuint RenderSystem::loadTexture(const std::string& name)
{
    auto itr = _textures.find(name);
    if(itr != _textures.end())
    {
        return itr->second;
    }
    auto data = _bridge.readImage(name);
    GLchar* ptr = (GLchar*)data->data();
    if(ptr == nullptr)
    {
        throw Exception(std::string("Could not read data for texture '")+name+"'.");
    }
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, ptr);
    _textures[name] = tex;
    LogDebug("loaded texture '%s' into %d", name.c_str(), tex);
    return tex;
}

GLuint RenderSystem::loadShader(const std::string& name, GLenum type)
{
    auto itr = _shaders.find(name);
    if(itr != _shaders.end())
    {
        return itr->second;
    }
    auto data = _bridge.readFile(name);
    const GLchar* ptr = (const GLchar*) data->data();
    if(ptr == nullptr)
    {
        throw Exception(std::string("Could not read data for shader '")+name+"'.");
    }

    GLuint shader = glCreateShader(type);
    GLint size = data->size();
    glShaderSource(shader, 1, &ptr, &size);
    glCompileShader(shader);
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status != GL_TRUE)
    {
        char buffer[512];
        glGetShaderInfoLog(shader, sizeof(buffer), NULL, buffer);
        throw Exception(buffer);
    }

    LogDebug("compiled shader '%s' into %d", name.c_str(), shader);
    _shaders[name] = shader;
    return shader;
}

std::shared_ptr<ProgramDefinition> RenderSystem::loadProgram(const std::string& name)
{
    auto itr = _programs.find(name);
    if(itr == _programs.end())
    {
        throw Exception(std::string("Could not find program '")+name+"'.");
    }
    auto& def = itr->second;
    if(def->id != 0)
    {
        return def;
    }

    GLuint vertexId = loadShader(def->vertex, GL_VERTEX_SHADER);
    GLuint fragmentId = loadShader(def->fragment, GL_FRAGMENT_SHADER);
    def->id = glCreateProgram();
    glAttachShader(def->id, vertexId);
    glAttachShader(def->id, fragmentId);
    glLinkProgram(def->id);
    for(auto& attr : def->attributes)
    {
        attr.second = glGetAttribLocation(def->id, attr.first.c_str());
    }
    for(auto& unif : def->uniforms)
    {
        unif.second = glGetUniformLocation(def->id, unif.first.c_str());
    }

    LogDebug("linked vertex '%s' and fragment '%s' into program %d", def->vertex.c_str(), def->fragment.c_str(), def->id);
    return def;
}

std::shared_ptr<MaterialDefinition> RenderSystem::loadMaterial(const std::string& name)
{
    auto itr = _materials.find(name);
    if(itr == _materials.end())
    {
        throw Exception(std::string("Could not find material '")+name+"'.");
    }
    auto& def = itr->second;    
    if(def->programDefinition != nullptr)
    {
        return def;
    }
    for(auto& texture : def->textures)
    {
        texture.second = loadTexture(texture.first);
    }
    def->programDefinition = loadProgram(def->program);
    LogDebug("loaded material '%s'", name.c_str());
    return def;
}

void RenderSystem::defineProgram(const std::string& name, const ProgramDefinition& definition)
{
    auto itr = _programs.find(name);
    if(itr != _programs.end())
    {
        throw Exception(std::string("Program '")+name+"' already defined.");
    }
    itr = _programs.insert(itr, {name, std::make_shared<ProgramDefinition>(definition)});
}

void RenderSystem::defineMaterial(const std::string& name, const MaterialDefinition& definition)
{
    auto itr = _materials.find(name);
    if(itr != _materials.end())
    {
        throw Exception(std::string("Material '")+name+"' already defined.");
    }
    itr = _materials.insert(itr, {name, std::make_shared<MaterialDefinition>(definition)});
}

void RenderSystem::update(entityx::EntityManager& es, entityx::EventManager& events, double dt)
{
    MaterialComponent::Handle material;
    for (entityx::Entity entity : es.entities_with_components(material))
    {
        if(material->definition == nullptr && !material->name.empty())
        {
            try
            {
                material->definition = loadMaterial(material->name);
            }
            catch(Exception e)
            {
                LogDebug("loadMaterial: %s", e.what());
                material->name = "";
            }
        }
    }
}
