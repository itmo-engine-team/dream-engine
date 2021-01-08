#pragma once

#include "BaseSceneViewer.h"

enum class ACF_Type;
enum class ACS_Type;
class ActorAssetInfo;

class ActorViewer : public BaseSceneViewer
{

public:

    ActorViewer(EngineConfigInfo* engineConfigInfo,
        InputSystem* inputSystem, Graphics* graphics, AssetManager* assetManager);

    bool LoadActor(ActorAssetInfo* actorAssetInfo);
    bool AddSceneComponent(ACS_Type type, const std::string& name);
    bool AddFixedComponent(ACF_Type type, const std::string& name);

    void Init() override;
    void Render() override;
    void RenderShadowMap() override;

private:

    ActorAssetInfo* actorAssetInfo;
    Actor* actor;

};

