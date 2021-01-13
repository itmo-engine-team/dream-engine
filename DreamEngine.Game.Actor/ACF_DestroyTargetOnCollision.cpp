#include "ACF_DestroyTargetOnCollision.h"
#include "GameAssetManager.h"

ACF_DestroyTargetOnCollision::ACF_DestroyTargetOnCollision(Actor* actor)
    : ACF_OnTargetCollision(actor)
{

}

void ACF_DestroyTargetOnCollision::onTargetCollision(Actor* targetActor)
{
    actor->GetContext()->GetGameAssetManager()->RequestToDeleteActor(targetActor);
}
