#include "ACF_OnTargetCollision.h"

#include "GameAssetManager.h"
#include "ParamString.h"
#include "ParamBool.h"

ACF_OnTargetCollision::ACF_OnTargetCollision(Actor* actor)
    : ActorComponentFixed(actor)
{
    targetTag = new ParamString();
    AddParam("Target Tag", targetTag);

    ignoreTriggerParam = new ParamBool();
    AddParam("Ignore trigger", ignoreTriggerParam);
}

void ACF_OnTargetCollision::onUpdate()
{
    targetActors.clear();
    targetActors = actor->GetContext()->GetGameAssetManager()->FindAllActorsByTag(targetTag->Get());

    for (auto targetActor : targetActors)
    {
        if (actor->GetContext()->GetGameAssetManager()->
            CheckActorsCollision(actor, targetActor, ignoreTriggerParam->Get()))
        {
            onTargetCollision(targetActor);
        }
    }
}
