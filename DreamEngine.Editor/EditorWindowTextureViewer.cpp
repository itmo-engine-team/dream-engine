#include "EditorWindowTextureViewer.h"

#include "imgui.h"

#include "Editor.h"
#include "AssetManager.h"
#include "TextureAssetInfo.h"
#include "AssetService.h"

EditorWindowTextureViewer::EditorWindowTextureViewer(Editor* editor, TextureAssetInfo* textureAssetInfo)
    : EditorWindow("Texture Viewer", editor), textureAssetInfo(textureAssetInfo)
{
    if (textureAssetInfo == nullptr)
        SetOpened(false);

    if (textureAssetInfo->GetTexturePath().length() > 0)
    {
        texturePath = textureAssetInfo->GetTexturePath();
    }
    else
    {
        texturePath = AssetService::CreateFolderPath(textureAssetInfo->GetAssetNode()->GetParent()) +
            textureAssetInfo->GetAssetNode()->GetName();
    }

    texturePath.resize(256);

    reimportTextureAsset();
}

void EditorWindowTextureViewer::Update()
{

}

void EditorWindowTextureViewer::Render()
{
    renderTextureViewer();
    renderTextureInspector();
}

void EditorWindowTextureViewer::renderTextureViewer()
{
    ImGui::Begin(GetName().data());

    if (ImGui::Button("Close"))
    {
        SetOpened(false);
    }

    ImGui::Separator();

    if (textureInstance != nullptr)
    {
        viewport->UpdateSize();
        ImGui::Image(textureInstance->GetShaderResourceView(), viewport->GetSize());
    }
    else
    {
        ImGui::Text("Texture is not valid");
    }

    ImGui::End();
}

void EditorWindowTextureViewer::renderTextureInspector()
{
    ImGui::Begin("Texture Inspector");

    if (ImGui::Button("Save"))
    {
        saveTextureAsset();
    }
    ImGui::SameLine();
    if (ImGui::Button("Reimport"))
    {
        reimportTextureAsset();
    }

    ImGui::Separator();

    ImGui::Text("Texture:");
    ImGui::InputText("Path", texturePath.data(), 256);

    ImGui::End();
}

void EditorWindowTextureViewer::saveTextureAsset()
{
    std::string stringTexturePath = texturePath.c_str();
    textureAssetInfo->SetTexturePath(stringTexturePath);

    editor->GetContext()->GetAssetManager()->SaveAsset(textureAssetInfo->GetAssetNode());

    reimportTextureAsset();
}

void EditorWindowTextureViewer::reimportTextureAsset()
{
    if (textureInstance != nullptr)
        delete textureInstance;

    std::string stringTexturePath = texturePath.c_str();
    std::wstring wstringTexturePath = std::wstring(stringTexturePath.begin(), stringTexturePath.end());
    textureInstance = new Texture(editor->GetContext()->GetGraphics(), wstringTexturePath.c_str());

    if (!textureInstance->IsValid())
    {
        delete textureInstance;
        textureInstance = nullptr;
    }
}
