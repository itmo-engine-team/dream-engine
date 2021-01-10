#include "ModelViewer.h"
#include "ACS_StaticModel.h"
#include "ErrorLogger.h"
#include "Texture.h"
#include "TextureAssetInfo.h"
#include "Transform.h"
#include "GameAssetManager.h"

ModelViewer::ModelViewer(EngineConfigInfo* engineConfigInfo,
                         InputSystem* inputSystem, Graphics* graphics, AssetManager* assetManager)
    : BaseSceneViewer(engineConfigInfo, inputSystem, graphics, assetManager)
{

}

bool ModelViewer::LoadModel(const std::string& modelPath, TextureAssetInfo* previewTextureInfo)
{
    if (previewTextureInfo != nullptr)
    {
        currentPreviewTexture = gameAssetManager->GetOrCreateTexture(previewTextureInfo->GetId());
    }
    else
    {
        currentPreviewTexture = nullptr;
    }

    currentModel = new ModelData(graphics->GetMeshRenderer(), modelPath);
    staticModelComponent->LoadModelData(currentModel);
    staticModelComponent->LoadTexture(currentPreviewTexture);
    staticModelComponent->UpdateTransform(new TransformInfo(Vector3::UnitY * -1 * currentModel->GetLowestVertexY()));

    return currentModel->IsValid();
}

void ModelViewer::Init()
{
    BaseSceneViewer::Init();

    modelActor = new Actor(actorContext);
    staticModelComponent = new ACS_StaticModel(modelActor);
    modelActor->AddSceneComponent(staticModelComponent);
    
    baseSceneActors.push_back(modelActor);
}

void ModelViewer::Render()
{
    BaseSceneViewer::Render();

    modelActor->Draw();
}

void ModelViewer::RenderShadowMap()
{
    BaseSceneViewer::RenderShadowMap();

    modelActor->DrawShadowMap();
}
