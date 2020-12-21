#include "A_Light.h"

A_Light::A_Light(Game* game, Transform* transform) : Actor(game, transform)
{
    lightComponent = new ACS_Light(game, this);
    AddSceneComponent(lightComponent);
}

ACS_Light* A_Light::GetLightComponent() const
{
    return lightComponent;
}
