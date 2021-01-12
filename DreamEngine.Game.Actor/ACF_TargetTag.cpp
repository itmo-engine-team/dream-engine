#include "ACF_TargetTag.h"

#include "ParamString.h"
#include "GameAssetManager.h"

ACF_TargetTag::ACF_TargetTag(Actor* actor) : ActorComponentFixed(actor)
{
    targetTag = new ParamString();
    AddParam("Target Tag", targetTag);
}

void ACF_TargetTag::findTargetActor()
{
    targetActor =  actor->GetContext()->GetGameAssetManager()->FindActorByTag(targetTag->Get());
}

Actor* ACF_TargetTag::GetTargetActor()
{
    return targetActor;
}

void ACF_TargetTag::onInit()
{
    findTargetActor();
}
