#pragma once

#include "BaseSceneViewer.h"

class ActorAssetInfo;

class ActorViewer : public BaseSceneViewer
{

public:

    ActorViewer(EngineConfigInfo* engineConfigInfo, InputSystem* inputSystem, Graphics* graphics);

    bool LoadActor(ActorAssetInfo* actorAssetInfo);

    void Init() override;
    void Render() override;
    void RenderShadowMap() override;

private:

    Actor* modelActor;

    ModelData* currentModel;
    Texture* currentPreviewTexture;

};

