//
//  Application.cpp
//  OpenglGame
//
//  Created by mibero on 14/10/14.
//  Copyright (c) 2014 Miguel Ibero. All rights reserved.
//

#include "game/Application.hpp"
#include "base/RenderSystem.hpp"
#include "base/Log.hpp"
#include "base/ProgramDefinition.hpp"
#include "base/MaterialDefinition.hpp"
#include "base/MaterialComponent.hpp"
#include "base/MeshComponent.hpp"

Application::Application()
{
    systems.add<RenderSystem>(_bridge);
    systems.configure();

    systems.system<RenderSystem>()->defineProgram("sprite",
        ProgramDefinition("shaders/sprite.vsh", "shaders/sprite.fsh")
        .withUniforms({"projView"})
        .withAttributes({"position", "texCoord", "color"}));

    systems.system<RenderSystem>()->defineMaterial("sprite",
        MaterialDefinition("sprite")
        .withTextures({"textures/checkers.jpg"}));
}

void Application::load()
{
    auto sprite = entities.create();
    sprite.assign<MaterialComponent>("sprite");
    sprite.assign<MeshComponent>();
}

void Application::unload()
{
    
}

void Application::update(double dt)
{
    systems.update<RenderSystem>(dt);
}