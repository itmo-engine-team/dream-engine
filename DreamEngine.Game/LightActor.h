#pragma once

#include "Actor.h"
#include "LightComponent.h"

class LightActor : public Actor
{

public:

    LightActor(Game* game, Transform* transform);

    LightComponent* GetLightComponent() const;

protected:

    LightComponent* lightComponent = nullptr;

};
