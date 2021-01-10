#pragma once

#include "BaseSceneViewer.h"

class TextureAssetInfo;
class ACS_StaticModel;
class ModelAssetInfo;

class ModelViewer : public BaseSceneViewer
{

public:

    ModelViewer(EngineConfigInfo* engineConfigInfo,
        InputSystem* inputSystem, Graphics* graphics, AssetManager* assetManager);

    bool LoadModel(const std::string& modelPath, TextureAssetInfo* previewTextureInfo);

    void Init() override;
    void Render() override;
    void RenderShadowMap() override;

private:

    Actor* modelActor;
    ACS_StaticModel* staticModelComponent;

    ModelData* currentModel;
    Texture* currentPreviewTexture;

};
