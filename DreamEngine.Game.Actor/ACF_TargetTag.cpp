#include "ACF_TargetTag.h"

#include "ParamString.h"
#include "ParamFloat.h"
#include "GameAssetManager.h"

ACF_TargetTag::ACF_TargetTag(Actor* actor) : ActorComponentFixed(actor)
{
    targetTag = new ParamString();
    AddParam("Target Tag", targetTag);

    fieldOfView = new ParamFloat(1);
    AddParam("Field of view", fieldOfView);
}

void ACF_TargetTag::findTargetActor()
{
    targetActor =  actor->GetContext()->GetGameAssetManager()->FindActorByTag(targetTag->Get());
}

Actor* ACF_TargetTag::GetTargetActor()
{
    return targetActor;
}

float ACF_TargetTag::GetFieldOfView()
{
    return fieldOfView->Get();
}

void ACF_TargetTag::onInit()
{
    findTargetActor();
}
