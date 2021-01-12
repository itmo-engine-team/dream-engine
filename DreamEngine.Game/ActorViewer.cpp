#include "ActorViewer.h"

#include "ErrorLogger.h"
#include "ActorAssetInfo.h"
#include "ActorFactory.h"
#include "ActorComponentFactory.h"

ActorViewer::ActorViewer(EngineConfigInfo* engineConfigInfo,
    InputSystem* inputSystem, Graphics* graphics, AssetManager* assetManager)
    : BaseSceneViewer(engineConfigInfo, inputSystem, graphics, assetManager)
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
    actor = ActorFactory::Create(actorContext, actorAssetInfo->GetActorType());

    LoadSceneComponents();
    LoadFixedComponents();

    return true;
}

void ActorViewer::LoadSceneComponents()
{
    for (auto sceneComponentInfo : actorAssetInfo->GetSceneComponents())
    {
        auto sceneComponent = ActorComponentFactory::CreateSceneComponent(actor, sceneComponentInfo);
        actor->AddSceneComponent(sceneComponent);
        sceneComponentInfo->SetComponentRef(sceneComponent);

        for (auto iter : sceneComponentInfo->GetParamExtender()->GetParamMap())
        {
            sceneComponent->UpdateParam(iter.first, iter.second);
        }

        sceneComponentInfo->GetParamExtender()->CopyParams(sceneComponent->GetParamMap());
    }
}

void ActorViewer::LoadFixedComponents()
{
    for (auto fixedComponentInfo : actorAssetInfo->GetFixedComponents())
    {
        auto fixedComponent = ActorComponentFactory::CreateFixedComponent(actor, fixedComponentInfo);
        actor->AddFixedComponent(fixedComponent);
        fixedComponentInfo->SetComponentRef(fixedComponent);

        for (auto iter : fixedComponentInfo->GetParamExtender()->GetParamMap())
        {
            fixedComponent->UpdateParam(iter.first, iter.second);
        }

        fixedComponentInfo->GetParamExtender()->CopyParams(fixedComponent->GetParamMap());
    }
}

bool ActorViewer::AddSceneComponent(ACS_Type type, const std::string& name)
{
    auto sceneComponentInfo = actorAssetInfo->AddSceneComponent(type, name);
    auto sceneComponent = ActorComponentFactory::CreateSceneComponent(actor, sceneComponentInfo);
    sceneComponentInfo->SetComponentRef(sceneComponent);
    sceneComponentInfo->GetParamExtender()->CopyParams(sceneComponent->GetParamMap());
    actor->AddSceneComponent(sceneComponent);

    return true;
}

bool ActorViewer::AddFixedComponent(ACF_Type type, const std::string& name)
{
    auto fixedComponentInfo = actorAssetInfo->AddFixedComponent(type, name);
    auto fixedComponent = ActorComponentFactory::CreateFixedComponent(actor, fixedComponentInfo);
    fixedComponentInfo->SetComponentRef(fixedComponent);
    fixedComponentInfo->GetParamExtender()->CopyParams(fixedComponent->GetParamMap());
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

    if (actor != nullptr)
    {
        actor->Draw();
    }
}

void ActorViewer::RenderShadowMap()
{
    BaseSceneViewer::RenderShadowMap();

    if (actor != nullptr)
    {
        actor->DrawShadowMap();
    }
}
