#pragma once

#include "ActorComponentFixed.h"

class ACF_PlayerMovement : public ActorComponentFixed
{

public:

    ACF_PlayerMovement(Actor* actor);

protected:

    void onUpdate() override;

    InputSystem* inputSystem;
};

