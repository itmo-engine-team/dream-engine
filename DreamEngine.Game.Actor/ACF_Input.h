#pragma once

#include "ActorComponentFixed.h"

class ACF_Input : public ActorComponentFixed
{

public:

    ACF_Input(Actor* actor);

protected:

    void onUpdate() override;

    InputSystem* inputSystem;
};

