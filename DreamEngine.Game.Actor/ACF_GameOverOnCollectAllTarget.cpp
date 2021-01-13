#include "ACF_GameOverOnCollectAllTarget.h"
#include "ParamString.h"
#include "GameAssetManager.h"

ACF_GameOverOnCollectAllTarget::ACF_GameOverOnCollectAllTarget(Actor* actor)
    : ActorComponentFixed(actor)
{
    targetTag = new ParamString();
    AddParam("Target Tag", targetTag);
}

void ACF_GameOverOnCollectAllTarget::onUpdate()
{
    auto targets = actor->GetContext()->GetGameAssetManager()->
        FindAllActorsByTag(targetTag->Get());

    if (targets.empty())
    {
        actor->GetContext()->GetGameAssetManager()->GameOver(true);
    }
}
