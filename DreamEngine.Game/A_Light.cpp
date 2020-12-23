#include "A_Light.h"

A_Light::A_Light(ActorContext* context, Transform* transform) : Actor(context, transform)
{
    lightComponent = new ACS_Light(context, this);
    AddSceneComponent(lightComponent);
}

ACS_Light* A_Light::GetLightComponent() const
{
    return lightComponent;
}
