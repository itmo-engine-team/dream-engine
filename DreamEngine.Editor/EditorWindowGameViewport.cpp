#include "EditorWindowGameViewport.h"

#include "imgui.h"
#include "Editor.h"
#include "Graphics.h"

EditorWindowGameViewport::EditorWindowGameViewport(Editor* editor)
    : EditorWindow("Game Viewport", editor)
{
    
}

void EditorWindowGameViewport::Update()
{

}

void EditorWindowGameViewport::Render()
{
    ImGui::Begin("GameViewport", nullptr, ImGuiWindowFlags_MenuBar);

    renderGameEditorMenu();

    if (ImGui::Button("Play")) 
    { 
        // TODO: Play game 
    }

    ImVec2 windowSize = ImGui::GetWindowSize();
    int sizeMul = windowSize.x / gameViewportSize.x;
    gameViewportSize = ImVec2(gameViewportSize.x * sizeMul, gameViewportSize.y * sizeMul);
    ImGui::Image(editor->GetGraphics()->GetSceneResourceView(), gameViewportSize);

    ImGui::End();
}

void EditorWindowGameViewport::renderGameEditorMenu()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Editor"))
        {
            if (ImGui::MenuItem("Save Layout", "")) {}
            if (ImGui::MenuItem("Load Layout", "")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Close All ", "")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}