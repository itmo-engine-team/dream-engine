#include "A_Light.h"

A_Light::A_Light(ActorContext* context) : Actor(context)
{
    lightComponent = new ACS_Light(this);
    AddSceneComponent(lightComponent);
}

ACS_Light* A_Light::GetLightComponent() const
{
    return lightComponent;
}
