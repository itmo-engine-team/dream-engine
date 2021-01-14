#include "ACF_DestroyByTime.h"
#include "ParamFloat.h"
#include "DeltaTimeHandler.h"
#include "GameAssetManager.h"

ACF_DestroyByTime::ACF_DestroyByTime(Actor* actor) : ActorComponentFixed(actor)
{
    timeToDestroyParam = new ParamFloat(1.0f);
    AddParam("Time to Destroy", timeToDestroyParam);
}

void ACF_DestroyByTime::onInit()
{
    currentTimeToDestroy = timeToDestroyParam->Get();
}

void ACF_DestroyByTime::onUpdate()
{
    if (currentTimeToDestroy < 0)
    {
        actor->GetContext()->GetGameAssetManager()->RequestToDeleteActor(actor);
        currentTimeToDestroy = 10000;
        return;
    }

    currentTimeToDestroy -= actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime();
}
