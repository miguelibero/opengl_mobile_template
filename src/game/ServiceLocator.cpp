#include "game/ServiceLocator.hpp"

ServiceLocator::ServiceLocator()
{
}

ServiceLocator& ServiceLocator::get()
{
    static ServiceLocator instance;
    return instance;
}

Input& ServiceLocator::getInput()
{
    return _input;
}

TextureManager& ServiceLocator::getTextureManager()
{
    return _textureManager;
}
