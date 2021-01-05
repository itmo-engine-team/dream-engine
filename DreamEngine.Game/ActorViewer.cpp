#include "ActorViewer.h"

#include "ErrorLogger.h"

ActorViewer::ActorViewer(EngineConfigInfo* engineConfigInfo, InputSystem* inputSystem, Graphics* graphics)
    : BaseSceneViewer(engineConfigInfo, inputSystem, graphics)
{

}

bool ActorViewer::LoadActor(ActorAssetInfo* actorAssetInfo)
{
    
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
