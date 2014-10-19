#include "base/TextureSystem.hpp"
#include "base/NativeBridge.hpp"
#include "base/TextureComponent.hpp"
#include "base/Log.hpp"
#include "base/Exception.hpp"

TextureSystem::TextureSystem(NativeBridge& bridge):
_bridge(bridge)
{
}

GLuint TextureSystem::getTexture(const std::string &name)
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


void TextureSystem::update(entityx::EntityManager& es, entityx::EventManager& events, double dt)
{
    TextureComponent::Handle texture;
    for (entityx::Entity entity : es.entities_with_components(texture))
    {
        if(texture->texture == 0)
        {
            try
            {
                texture->texture = getTexture(texture->name);
            }
            catch(Exception e)
            {
                texture->texture = -1;
            }
        }
    }
}
