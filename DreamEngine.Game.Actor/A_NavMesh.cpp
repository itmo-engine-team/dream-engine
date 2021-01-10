#include "A_NavMesh.h"
#include "ACS_Camera.h"
#include "ACS_Light.h"
#include "NavMesh.h"
#include "ACS_StaticModel.h"
#include "Transform.h"

A_NavMesh::A_NavMesh(ActorContext* context) : Actor(context)
{
    navMesh = new NavMesh(transform->GetWorldPosition(), { 6, 1, 6 }, 0.5f);
    this->context->SetNavMesh(navMesh);

    staticModelComponent = new ACS_StaticModel(this, navMesh->GetModelData());
    AddSceneComponent(staticModelComponent);
}

NavMesh* A_NavMesh::GetNavMesh() const
{
    return navMesh;
}

void A_NavMesh::onUpdate()
{
    staticModelComponent->LoadModelData(navMesh->GetModelData());
}
