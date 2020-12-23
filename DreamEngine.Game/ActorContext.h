#pragma once

#include "Graphics.h"
#include "InputSystem.h"
#include "DeltaTimeHandler.h"

struct ActorContext
{

    Graphics* graphics;
    InputSystem* inputSystem;
    DeltaTimeHandler* deltaTimeHandler;

    ActorContext(Graphics* graphics, InputSystem* inputSystem, DeltaTimeHandler* deltaTimeHandler)
        : graphics(graphics), inputSystem(inputSystem), deltaTimeHandler(deltaTimeHandler) {}

};

