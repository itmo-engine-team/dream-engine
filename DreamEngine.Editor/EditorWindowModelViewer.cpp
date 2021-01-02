#include "EditorWindowModelViewer.h"

#include "imgui.h"
#include "ModelAssetInfo.h"

EditorWindowModelViewer::EditorWindowModelViewer(Editor* editor, ModelAssetInfo* modelAssetInfo)
    : EditorWindow("Model Viewer", editor), modelAssetInfo(modelAssetInfo)
{
    if (modelAssetInfo == nullptr)
        SetOpened(false);
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

    ImGui::InputText("Model Path: ", modelPath, IM_ARRAYSIZE(modelPath));

    ImGui::Text("Preview Texture: ");
    ImGui::Text(previewTextureAssetName.c_str());
    ImGui::SameLine();
    if (ImGui::Button("Choose"))
    {
        assetChooser = new EditorPopupModalAssetChooser(editor, AssetType::Texture);
    }

    ImGui::End();
}

void EditorWindowModelViewer::drawAssetChooser()
{
    if (!EditorPopupModal::DrawPipeline(assetChooser))
        return;

    if (assetChooser->GetResult())
    {
        previewTextureAssetName = assetChooser->GetChosenAsset()->GetName();
    }
}

void EditorWindowModelViewer::saveModelAsset()
{
    std::string stringModelPath = modelPath;
    modelAssetInfo->SetModelPath(stringModelPath);

    editor->GetContext()->GetAssetManager()->SaveAsset(modelAssetInfo->GetAssetNode());

    reimportModelAsset();
}

void EditorWindowModelViewer::reimportModelAsset()
{
    // TODO Implement logic
}
