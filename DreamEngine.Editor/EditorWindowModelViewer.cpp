#include "EditorWindowModelViewer.h"

#include "imgui.h"

EditorWindowModelViewer::EditorWindowModelViewer(Editor* editor)
    : EditorWindow("Model Viewer", editor)
{

}

void EditorWindowModelViewer::Update()
{
}

void EditorWindowModelViewer::Render()
{
    renderModelViewer();
    renderModelInspector();
}

bool EditorWindowModelViewer::GetResult()
{
    return result;
}

void EditorWindowModelViewer::renderModelViewer()
{
    ImGui::Begin(GetName().data());

    ImGui::End();
}

void EditorWindowModelViewer::renderModelInspector()
{
    ImGui::Begin("Model Inspector");

    if (ImGui::Button("Save"))
    {
        //TODO : save and close
        result = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("Reimport"))
    {
        //TODO : reimport asset
    }

    static char modelPath[128] = "";
    ImGui::InputText("Model Path: ", modelPath, IM_ARRAYSIZE(modelPath));

    ImGui::Text("Preview Texture: ");
    ImGui::Text("Texture name");
    ImGui::SameLine();
    if (ImGui::Button("Choose"))
    {
        //TODO : open asset chooser 
    }

    ImGui::End();
}
