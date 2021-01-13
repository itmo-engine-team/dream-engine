#include "ACS_Collision.h"
#include "ParamFloat.h"
#include "MeshRenderer.h"
#include "MeshObject.h"
#include "LightBuffer.h"
#include "CameraBuffer.h"
#include "ConstantBuffer.h"
#include "ACS_Camera.h"
#include "ACS_Light.h"
#include "ParamBool.h"

ACS_Collision::ACS_Collision(Actor* actor, Vector2 size) : ActorComponentScene(actor), size(size)
{
    drawCollisionParam = new ParamBool(false);
    sizeParamX = new ParamFloat(1.0f);
    sizeParamY = new ParamFloat(1.0f);
    AddParam("Draw Collision", drawCollisionParam);
    AddParam("Size X", sizeParamX);
    AddParam("Size Y", sizeParamY);

    createDebugMeshObject();
}

ACS_Collision::~ACS_Collision()
{
    delete debugMeshObject;
    delete debugModelData;
}

Vector2 ACS_Collision::GetWorldSize() const
{
    Vector3 worldScale = transform->GetWorldScale();
    return { size.x * worldScale.x, size.y * worldScale.z };
}

Vector2 ACS_Collision::GetSize()
{
    return size;
}

void ACS_Collision::SetSize(Vector2 newSize)
{
    size = newSize;
}

bool ACS_Collision::IsPointIntersects(Vector3 targetLocation)
{
    Vector2 worldSize = GetWorldSize();
    float leftCollisionEdge = transform->GetWorldPosition().x - worldSize.x;
    float rightCollisionEdge = transform->GetWorldPosition().x + worldSize.x;
    float topCollisionEdge = transform->GetWorldPosition().z + worldSize.y;
    float downCollisionEdge = transform->GetWorldPosition().z - worldSize.y;

    if (max(leftCollisionEdge, targetLocation.x) <= min(rightCollisionEdge, targetLocation.x) &&
        max(downCollisionEdge, targetLocation.z) <= min(topCollisionEdge, targetLocation.z))
    {
        return true;
    }

    return false;
}

bool ACS_Collision::IsCollisionIntersects(Vector3 targetLocation, Vector2 targetCollisionSize)
{
    Vector2 worldSize = GetWorldSize();
    float leftCollisionEdge = transform->GetWorldPosition().x - worldSize.x;
    float rightCollisionEdge = transform->GetWorldPosition().x + worldSize.x;
    float topCollisionEdge = transform->GetWorldPosition().z + worldSize.y;
    float downCollisionEdge = transform->GetWorldPosition().z - worldSize.y;

    float targetLeftCollisionEdge = targetLocation.x - targetCollisionSize.x;
    float targetRightCollisionEdge = targetLocation.x + targetCollisionSize.x;
    float targetTopCollisionEdge = targetLocation.z + targetCollisionSize.y;
    float targetDownCollisionEdge = targetLocation.z - targetCollisionSize.y;

    if (max(leftCollisionEdge, targetLeftCollisionEdge) <= min(rightCollisionEdge, targetRightCollisionEdge) &&
        max(downCollisionEdge, targetDownCollisionEdge) <= min(topCollisionEdge, targetTopCollisionEdge))
    {
        return true;
    }

    return false;
}

void ACS_Collision::onDraw()
{
    if (!drawCollisionParam->Get()) return;

    const ConstantBuffer cb =
    {
        transform->GetWorldMatrix(),
        actor->GetContext()->GetCamera()->GetViewMatrix(),
        actor->GetContext()->GetCamera()->GetProjectionMatrix(),
        actor->GetContext()->GetLight()->GetViewMatrix(),
        actor->GetContext()->GetLight()->GetProjectionMatrix(),
    };

    const LightBuffer lb =
    {
        Vector4{1.0f, 1.0f, 1.0f, 1.0f},
        Vector4{1.0f, 1.0f, 1.0f, 1.0f},
        actor->GetContext()->GetLight()->GetDirection(),
        100.0f,
        {1.0f, 1.0f, 1.0f, 1.0f }
    };

    const CameraBuffer cameraBufferData =
    {
        actor->GetContext()->GetCamera()->GetTransform()->GetWorldPosition()
    };

    debugMeshObject->Render(cb, lb, cameraBufferData);
}

void ACS_Collision::onParamUpdate(std::string name, BaseParam* param)
{
    ActorComponentScene::onParamUpdate(name, param);

    if (param == sizeParamX || param == sizeParamY)
    {
        size = Vector2 { sizeParamX->Get(), sizeParamY->Get() };
        delete debugMeshObject;
        delete debugModelData;
        createDebugMeshObject();
    }
}

void ACS_Collision::createDebugMeshObject()
{
    debugModelData = actor->GetContext()->GetGraphics()->GetMeshRenderer()->
        CreateBoxModel({ 1, 0, 0, 1 }, { size.x, 0.5f, size.y });
    const auto debugMeshData = debugModelData->GetMeshDataList()[0];
    debugMeshObject = new MeshObject(actor->GetContext()->GetGraphics(), 
        debugMeshData, nullptr);
}
