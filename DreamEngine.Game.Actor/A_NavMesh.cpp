#include "A_NavMesh.h"
#include "ACS_Camera.h"
#include "ACS_Light.h"
#include "NavMesh.h"
#include "ACS_StaticModel.h"
#include "Transform.h"

A_NavMesh::A_NavMesh(ActorContext* context, Transform* transform) : Actor(context, transform)
{
    navMesh = new NavMesh(transform->GetWorldPosition(), { 6, 1, 6 }, 0.5f);
    this->context->SetNavMesh(navMesh);
}

NavMesh* A_NavMesh::GetNavMesh() const
{
    return navMesh;
}

void A_NavMesh::onUpdate()
{
    ACS_StaticModel* staticModelComponent = FindComponent<ACS_StaticModel>();
    if (staticModelComponent != nullptr)
        RemoveComponent(staticModelComponent);

    AddSceneComponent(new ACS_StaticModel(this,
        new Transform(Vector3::Zero), navMesh->GetModelData()));
}
