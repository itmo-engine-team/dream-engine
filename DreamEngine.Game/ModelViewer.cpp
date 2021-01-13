#include "ModelViewer.h"
#include "ACS_StaticModel.h"
#include "ErrorLogger.h"
#include "Texture.h"
#include "TextureAssetInfo.h"
#include "Transform.h"
#include "GameAssetManager.h"
#include "ModelAssetInfo.h"
#include "ParamBool.h"
#include "ParamVector3.h"
#include "MeshRenderer.h"

ModelViewer::ModelViewer(EngineConfigInfo* engineConfigInfo,
                         InputSystem* inputSystem, Graphics* graphics, AssetManager* assetManager)
    : BaseSceneViewer(engineConfigInfo, inputSystem, graphics, assetManager)
{

}

bool ModelViewer::LoadModel(ModelAssetInfo* modelAssetInfo, TextureAssetInfo* previewTextureInfo)
{
    if (previewTextureInfo != nullptr)
    {
        currentPreviewTexture = gameAssetManager->GetOrCreateTexture(previewTextureInfo->GetId());
    }
    else
    {
        currentPreviewTexture = nullptr;
    }

    delete currentModel;
    if (modelAssetInfo->GetUseDefaultBoxParam()->Get())
    {
        auto boxColor = modelAssetInfo->GetDefaultBoxColorParam()->Get();
        currentModel = graphics->GetMeshRenderer()->CreateBoxModel(
            { boxColor.x, boxColor.y, boxColor.z, 1.0f }, { 1.0f, 1.0f, 1.0f });
    }
    else
    {
        currentModel = new ModelData(graphics->GetMeshRenderer(), modelAssetInfo->GetModelPath());
    }
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
