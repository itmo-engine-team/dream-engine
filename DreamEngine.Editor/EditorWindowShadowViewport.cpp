#include "EditorWindowShadowViewport.h"

#include "imgui.h"
#include "Editor.h"
#include "Graphics.h"

EditorWindowShadowViewport::EditorWindowShadowViewport(Editor* editor)
    : EditorWindow("Shadow Viewport", editor)
{

}

void EditorWindowShadowViewport::Update()
{

}

void EditorWindowShadowViewport::Render()
{
    ImGui::Begin("ShadowRender");
    ImGui::Image(editor->GetContext()->GetGraphics()->GetShadowMapResourceView(),
        ImVec2(300, 300));
    ImGui::End();
}
