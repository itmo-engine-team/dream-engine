#include "ModelViewer.h"
#include "ACS_StaticModel.h"
#include "ErrorLogger.h"
#include "Texture.h"
#include "TextureAssetInfo.h"
#include "Transform.h"

ModelViewer::ModelViewer(EngineConfigInfo* engineConfigInfo,
    InputSystem* inputSystem, Graphics* graphics, AssetManager* assetManager)
    : BaseSceneViewer(engineConfigInfo, inputSystem, graphics, assetManager)
{

}

bool ModelViewer::LoadModel(const std::string& modelPath, TextureAssetInfo* previewTextureInfo)
{
    if (currentModel != nullptr)
    {
        auto component = modelActor->FindComponent<ACS_StaticModel>();
        if (component == nullptr)
        {
            ErrorLogger::Log(Error,
                "ModelViewer - Model was loaded, but there is no component on it");
            return false;
        }

        modelActor->RemoveComponent(component);

        delete currentModel;
        currentModel = nullptr;

        if (currentPreviewTexture != nullptr)
        {
            delete currentPreviewTexture;
            currentPreviewTexture = nullptr;
        }
    }

    if (previewTextureInfo != nullptr)
    {
        auto texturePath = std::wstring(previewTextureInfo->GetTexturePath().begin(),
            previewTextureInfo->GetTexturePath().end());
        currentPreviewTexture = new Texture(graphics, texturePath.c_str());
    }
    else
    {
        currentPreviewTexture = nullptr;
    }

    currentModel = new ModelData(graphics->GetMeshRenderer(), modelPath, currentPreviewTexture);
    modelActor->AddSceneComponent(new ACS_StaticModel(modelActor, currentModel));
    modelActor->FindComponent<ACS_StaticModel>()->UpdateTransform(new TransformInfo(Vector3::UnitY * -1 * currentModel->GetLowestVertexY()));

    return currentModel->IsValid();
}

void ModelViewer::Init()
{
    BaseSceneViewer::Init();

    modelActor = new Actor(actorContext);
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
