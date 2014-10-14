#ifndef __opengl_sample__TextureManager__
#define __opengl_sample__TextureManager__

#include <iostream>
#include <map>
#include <string>
#include <base/Gl.hpp>

class TextureManager
{
    typedef std::map<std::string, GLuint> Textures;
    
    Textures _textures;
    
public:
    GLuint getTexture(const std::string& name);
    
private:
    GLuint createTexture(const std::string& name);
};

#endif /* defined(__opengl_sample__TextureManager__) */
