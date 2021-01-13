#include "A_NavMesh.h"
#include "ACS_Camera.h"
#include "ACS_Light.h"
#include "NavMesh.h"
#include "ACS_StaticModel.h"
#include "GameAssetManager.h"
#include "ACS_Collision.h"

A_NavMesh::A_NavMesh(ActorContext* context) : Actor(context)
{
    navMesh = new NavMesh({ 0, 0.11f, 0 }, { 24, 1, 24 }, 0.5f);
    this->context->SetNavMesh(navMesh);

    staticModelComponent = new ACS_StaticModel(this, navMesh->GetModelData());
    AddSceneComponent(staticModelComponent);
}

NavMesh* A_NavMesh::GetNavMesh() const
{
    return navMesh;
}

void A_NavMesh::onInit()
{

}

void A_NavMesh::onUpdate()
{
    if (context->GetInputSystem()->IsKeyPressed(KeyboardInput::Key_P))
    {
        if (keyIsReleased)
        {
            navMesh->SetIsDebug(!navMesh->IsDebug());
            keyIsReleased = false;
        }
    }
    else
    {
        keyIsReleased = true;
    }

    navMesh->ResetPolygons();

    for (auto collision : context->GetGameAssetManager()->GetCollisions())
    {
        if (collision->IsTrigger() || collision->IsActive()) return;

        navMesh->UpdatePolygons(collision->GetActor(),
            collision->GetTransform()->GetWorldPosition(), collision->GetWorldSize());
    }

    staticModelComponent->LoadModelData(navMesh->GetModelData());
}
