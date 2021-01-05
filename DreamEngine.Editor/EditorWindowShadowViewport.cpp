#include "EditorWindowShadowViewport.h"

#include "imgui.h"
#include "Editor.h"
#include "Graphics.h"
#include "Game.h"

EditorWindowShadowViewport::EditorWindowShadowViewport(Editor* editor)
    : EditorWindow("Shadow Viewport", editor)
{
    SetOpened(false);
}

void EditorWindowShadowViewport::Update()
{

}

void EditorWindowShadowViewport::Render()
{
    ImGui::Begin("ShadowRender");
    ImGui::Image(editor->GetContext()->GetGame()->GetSceneRenderer()->GetShadowMapResourceView(),
        ImVec2(300, 300));
    ImGui::End();
}
