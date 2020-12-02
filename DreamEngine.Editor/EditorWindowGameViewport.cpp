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
    ImGui::Begin("GameViewport");
    ImGui::Image(editor->GetGraphics()->GetSceneResourceView(), ImVec2(400, 300));
    ImGui::End();
}
