#include "LightActor.h"

#include "Engine.h"

LightActor::LightActor(Game* game, Transform* transform) : Actor(game, transform)
{
    lightComponent = new LightComponent(game, this);
    AddComponent(lightComponent);
}

LightComponent* LightActor::GetLightComponent() const
{
    return lightComponent;
}
