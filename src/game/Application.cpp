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
#include "base/TextureComponent.hpp"
#include "base/TransformComponent.hpp"

Application::Application()
{
    systems.add<RenderSystem>();
    systems.add<TextureSystem>(_bridge);
    systems.configure();
}

void Application::load()
{
    auto sprite = entities.create();
    sprite.assign<TextureComponent>("sprite.png");
    sprite.assign<TransformComponent>();
}

void Application::unload()
{
    
}

void Application::update(double dt)
{
    systems.update<RenderSystem>(dt);
}