#include "EditorWindowShadowViewport.h"

#include "imgui.h"
#include "Graphics.h"

EditorWindowShadowViewport::EditorWindowShadowViewport(Graphics* graphics)
    : EditorWindow("Shadow Viewport", graphics)
{

}

void EditorWindowShadowViewport::Update()
{

}

void EditorWindowShadowViewport::Render()
{
    ImGui::Begin("ShadowRender");
    ImGui::Image(graphics->GetShadowMapResourceView(), ImVec2(300, 300));
    ImGui::End();
}
