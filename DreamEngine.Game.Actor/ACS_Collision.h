#pragma once

#include "ActorComponentScene.h"
#include "Transform.h"

class ParamVector3;
class ParamFloat;
class ParamBool;
class MeshObject;
class ModelData;

class ACS_Collision : public ActorComponentScene
{

public:

    ACS_Collision(Actor* actor);
    ~ACS_Collision() override;

    bool IsTrigger() const;

    Vector2 GetWorldSize() const;
    Vector2 GetSize();

    bool IsPointIntersects(Vector3 targetLocation);
    bool IsCollisionIntersects(Vector3 targetLocation, Vector2 targetCollisionSize);

protected:

    ParamVector3* sizeParam;
    ParamBool* isTriggerParam;
    ParamBool* drawCollisionParam;
    MeshObject* debugMeshObject = nullptr;
    ModelData* debugModelData = nullptr;

    void onDraw() override;
    void onParamUpdate(std::string name, BaseParam* param) override;

    void createDebugMeshObject();

};

class ACS_Creator_Collision : public ACS_Creator
{

public:

    ActorComponentScene* Create(Actor* actor, ActorComponentSceneInfo* actorInfo) override
    {
        return new ACS_Collision(actor);
    }

};
