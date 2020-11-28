#include "EditorWindowGameViewport.h"

#include "imgui.h"
#include "Graphics.h"

EditorWindowGameViewport::EditorWindowGameViewport(Graphics* graphics)
    : EditorWindow("Game Viewport", graphics)
{

}

void EditorWindowGameViewport::Update()
{

}

void EditorWindowGameViewport::Render()
{
    ImGui::Begin("GameViewport");
    ImGui::Image(graphics->GetSceneResourceView(), ImVec2(400, 300));
    ImGui::End();
}
