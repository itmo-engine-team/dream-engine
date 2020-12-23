#pragma once

class Graphics;
class InputSystem;

struct ActorContext
{

    Graphics* graphics;
    InputSystem* inputSystem;

    ActorContext(Graphics* graphics, InputSystem* inputSystem)
        : graphics(graphics), inputSystem(inputSystem) {}

};

