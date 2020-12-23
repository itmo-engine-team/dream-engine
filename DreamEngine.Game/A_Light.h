#pragma once

#include "Actor.h"
#include "ACS_Light.h"

class A_Light : public Actor
{

public:

    A_Light(ActorContext context, Transform* transform);

    ACS_Light* GetLightComponent() const;

protected:

    ACS_Light* lightComponent = nullptr;

};
