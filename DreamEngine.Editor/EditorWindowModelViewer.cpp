#include "EditorWindowModelViewer.h"

#include "imgui.h"
#include "ModelAssetInfo.h"
#include "AssetService.h"
#include "ModelViewer.h"

EditorWindowModelViewer::EditorWindowModelViewer(Editor* editor, ModelAssetInfo* modelAssetInfo)
    : EditorWindow("Model Viewer", editor), modelAssetInfo(modelAssetInfo)
{
    if (modelAssetInfo == nullptr)
        SetOpened(false);
    
    paramBool = modelAssetInfo->GetUseDefaultBoxParam();
    paramVector3 = modelAssetInfo->GetDefaultBoxColorParam();
    paramDrawerBool = new EditorParamDrawerBool(0, "Draw standard box: ", paramBool);  
    paramDrawVector3 = new EditorParamDrawerVector3(1, "Box Color:", paramVector3);
}

void EditorWindowModelViewer::Init()
{
    if (modelAssetInfo == nullptr)
        return;

    if (modelAssetInfo->GetModelPath().length() > 0)
    {
        modelPath = modelAssetInfo->GetModelPath();
    }
    else
    {
        modelPath = AssetService::CreateFolderPath(modelAssetInfo->GetAssetNode()->GetParent()) +
            modelAssetInfo->GetAssetNode()->GetName();
    }

    modelPath.resize(256);

    reimportModelAsset();
}

void EditorWindowModelViewer::Update()
{
}

void EditorWindowModelViewer::Render()
{
    renderModelViewer();
    renderModelInspector();
    drawAssetChooser();
}

void EditorWindowModelViewer::renderModelViewer()
{
    ImGui::Begin(GetName().data());
    
    if (ImGui::Button("Close"))
    {
        SetOpened(false);
    }

    ImGui::Separator();

    if (!isModelValid)
    {
        ImGui::Text("Model is not valid. Please check path.");
    }

    viewport->UpdateSize();
    ImGui::Image(editor->GetContext()->GetModelViewer()->GetSceneRenderer()->GetSceneResourceView(),
        viewport->GetSize());

    ImGui::End();
}

void EditorWindowModelViewer::renderModelInspector()
{
    ImGui::Begin("Model Inspector");

    if (ImGui::Button("Save"))
    {
        saveModelAsset();
    }
    ImGui::SameLine();
    if (ImGui::Button("Reimport"))
    {
        reimportModelAsset();
    }

    ImGui::Separator();

    paramDrawerBool->Draw();
    if (!paramBool->Get())
    {
        ImGui::Text("Model:");
        ImGui::InputText("Path", modelPath.data(), 256);

        ImGui::Text("Preview Texture: ");
        ImGui::Text(previewTextureAsset != nullptr ? previewTextureAsset->GetName().c_str() : "Green Color");
        ImGui::SameLine();
        if (ImGui::Button("Choose"))
        {
            assetChooser = new EditorPopupModalAssetChooser(editor, AssetType::Texture);
        }
    }
    else
    {
        paramDrawVector3->Draw();
    }

    ImGui::End();
}

void EditorWindowModelViewer::drawAssetChooser()
{
    if (!EditorPopupModal::DrawPipeline(assetChooser))
        return;

    if (assetChooser->GetResult())
    {
        if (assetChooser->GetChosenAsset() == nullptr)
            previewTextureAsset = nullptr;
        else 
            previewTextureAsset = dynamic_cast<TextureAssetInfo*>(assetChooser->GetChosenAsset());
        reimportModelAsset();

        delete assetChooser;
        assetChooser = nullptr;
    }
}

void EditorWindowModelViewer::saveModelAsset()
{
    std::string stringModelPath = modelPath.c_str();
    modelAssetInfo->SetModelPath(stringModelPath);

    editor->GetContext()->GetAssetManager()->SaveAsset(modelAssetInfo->GetAssetNode());

    reimportModelAsset();
}

void EditorWindowModelViewer::reimportModelAsset()
{
    std::string stringModelPath = modelPath.c_str();
    isModelValid = editor->GetContext()->GetModelViewer()->
        LoadModel(stringModelPath, previewTextureAsset);
}
