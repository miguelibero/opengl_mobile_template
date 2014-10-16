#include "base/TextureSystem.hpp"
#include "base/NativeBridge.hpp"
#include "base/TextureComponent.hpp"

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
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, data.get());
    _textures[name] = tex;
    return tex;
}


void TextureSystem::update(entityx::EntityManager& es, entityx::EventManager& events, double dt)
{
    TextureComponent::Handle texture;
    for (entityx::Entity entity : es.entities_with_components(texture))
    {
        
    }
}
