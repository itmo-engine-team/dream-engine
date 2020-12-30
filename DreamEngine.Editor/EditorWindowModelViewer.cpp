#include "EditorWindowModelViewer.h"

#include "imgui.h"

EditorWindowModelViewer::EditorWindowModelViewer(Editor* editor, AssetType currentAssetType, Texture* assetIcon)
    : EditorWindow("Model Viewer", editor)
{
    assetType = currentAssetType;
    currentTexture = assetIcon;
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

bool EditorWindowModelViewer::GetResult()
{
    return result;
}

void EditorWindowModelViewer::renderModelViewer()
{
    ImGui::Begin(GetName().data());
    
    if (ImGui::Button("Close"))
    {
        result = true;
    }

    ImGui::End();
}

void EditorWindowModelViewer::renderModelInspector()
{
    ImGui::Begin("Model Inspector");

    if (ImGui::Button("Save"))
    {
        //TODO : save 
    }
    ImGui::SameLine();
    if (ImGui::Button("Reimport"))
    {
        //TODO : reimport asset
    }

    static char modelPath[128] = "";
    ImGui::InputText("Model Path: ", modelPath, IM_ARRAYSIZE(modelPath));

    ImGui::Text("Preview Texture: ");
    ImGui::Text(currentAssetInfoName.c_str());
    ImGui::SameLine();
    if (ImGui::Button("Choose"))
    {
        //TODO : open asset chooser 
        assetChooser = new EditorPopupModelAssetChooser(editor, assetType, currentTexture);
    }

    ImGui::End();
}

void EditorWindowModelViewer::drawAssetChooser()
{
    if (!EditorPopupModal::DrawPipeline(assetChooser))
        return;

    if (assetChooser->GetResult())
    {
        currentAssetInfoName = assetChooser->GetCurrentAsset()->GetName();
    }
}
