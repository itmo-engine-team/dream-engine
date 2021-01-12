#pragma once

#include "ActorComponentScene.h"
#include "Transform.h"

class ParamFloat;
class ParamBool;
class MeshObject;
class ModelData;

class ACS_Collision : public ActorComponentScene
{

public:

    ACS_Collision(Actor* actor, Vector2 size = Vector2 { 1.0f, 1.0f });
    ~ACS_Collision() override;

    Vector2 GetSize();
    void SetSize(Vector2 newSize);

protected:

    ParamFloat* sizeParamX;
    ParamFloat* sizeParamY;
    ParamBool* drawCollisionParam;
    Vector2 size;
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
