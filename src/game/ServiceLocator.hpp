#ifndef __opengl_game__ServiceLocator__
#define __opengl_game__ServiceLocator__

#include "base/Input.hpp"
#include "base/TextureManager.hpp"

class ServiceLocator
{
    Input _input;
    TextureManager _textureManager;
    
private:
    ServiceLocator();

public:
	static ServiceLocator& get();

    Input& getInput();
    TextureManager& getTextureManager();
};

#endif /* defined(__opengl_game__ServiceLocator__) */
