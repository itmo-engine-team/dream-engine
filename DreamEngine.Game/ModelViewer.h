#pragma once

#include "BaseSceneViewer.h"

class TextureAssetInfo;
class ModelAssetInfo;

class ModelViewer : public BaseSceneViewer
{

public:

    ModelViewer(EngineConfigInfo* engineConfigInfo, InputSystem* inputSystem, Graphics* graphics);

    bool LoadModel(const std::string& modelPath, TextureAssetInfo* previewTextureInfo);

    void Init() override;
    void Render() override;
    void RenderShadowMap() override;

private:

    Actor* modelActor;

    ModelData* currentModel;
    Texture* currentPreviewTexture;

};

