#include "ActorViewer.h"

#include "ErrorLogger.h"
#include "ActorAssetInfo.h"
#include "ActorFactory.h"
#include "ActorComponentFactory.h"

ActorViewer::ActorViewer(EngineConfigInfo* engineConfigInfo, InputSystem* inputSystem, Graphics* graphics)
    : BaseSceneViewer(engineConfigInfo, inputSystem, graphics)
{

}

bool ActorViewer::LoadActor(ActorAssetInfo* actorAssetInfo)
{
    if (actor != nullptr)
    {
        delete actor;
        actor = nullptr;
    }

    this->actorAssetInfo = actorAssetInfo;
    actor = ActorFactory::Create(actorContext, actorAssetInfo->GetActorType(), new TransformInfo());

    return true;
}

bool ActorViewer::AddSceneComponent(ACS_Type type, const std::string& name)
{
    auto sceneComponentInfo = actorAssetInfo->AddSceneComponent(type, name);
    auto sceneComponent = ActorComponentFactory::CreateSceneComponent(actor, sceneComponentInfo);
    sceneComponentInfo->SetComponentRef(sceneComponent);
    actor->AddSceneComponent(sceneComponent);

    return true;
}

bool ActorViewer::AddFixedComponent(ACF_Type type, const std::string& name)
{
    auto fixedComponentInfo = actorAssetInfo->AddFixedComponent(type, name);
    auto fixedComponent = ActorComponentFactory::CreateFixedComponent(actor, fixedComponentInfo);
    fixedComponentInfo->SetComponentRef(fixedComponent);
    actor->AddFixedComponent(fixedComponent);

    return true;
}

void ActorViewer::Init()
{
    BaseSceneViewer::Init();
    
}

void ActorViewer::Render()
{
    BaseSceneViewer::Render();

}

void ActorViewer::RenderShadowMap()
{
    BaseSceneViewer::RenderShadowMap();

}
