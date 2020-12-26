#include "A_NavMesh.h"
#include "ACS_Camera.h"
#include "ACS_Light.h"
#include "NavMesh.h"
#include "ACS_StaticModel.h"

A_NavMesh::A_NavMesh(ActorContext* context, Transform* transform) : Actor(context, transform)
{
    navMesh = new NavMesh(transform->GetWorldPosition(), { 3, 1, 3 }, 1);

    ModelData* modelData = new ModelData();
    modelData->AddMeshData(navMesh->GetMeshData());
    AddSceneComponent(new ACS_StaticModel(context, this, new Transform(Vector3::Zero), modelData));
}
