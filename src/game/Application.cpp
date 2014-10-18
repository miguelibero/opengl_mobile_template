//
//  Application.cpp
//  OpenglGame
//
//  Created by mibero on 14/10/14.
//  Copyright (c) 2014 Miguel Ibero. All rights reserved.
//

#include "game/Application.hpp"
#include "base/RenderSystem.hpp"
#include "base/TextureSystem.hpp"
#include "base/ShaderSystem.hpp"
#include "base/TransformComponent.hpp"
#include "base/TextureComponent.hpp"
#include "base/ShaderComponent.hpp"
#include "base/Log.hpp"

Application::Application()
{
    systems.add<RenderSystem>();
    systems.add<TextureSystem>(_bridge);
    systems.add<ShaderSystem>(_bridge);
    systems.configure();
}

void Application::load()
{
    auto sprite = entities.create();
    sprite.assign<TextureComponent>("checkers.jpg");
    sprite.assign<ShaderComponent>("sprite");
    sprite.assign<TransformComponent>();
}

void Application::unload()
{
    
}

void Application::update(double dt)
{
	systems.update<ShaderSystem>(dt);
	systems.update<TextureSystem>(dt);
    systems.update<RenderSystem>(dt);
}