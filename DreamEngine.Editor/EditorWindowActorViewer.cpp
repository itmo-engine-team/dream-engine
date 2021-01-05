#include "EditorWindowActorViewer.h"

#include "imgui.h"
#include "ModelAssetInfo.h"
#include "ModelViewer.h"
#include "ActorAssetInfo.h"

EditorWindowActorViewer::EditorWindowActorViewer(Editor* editor, ActorAssetInfo* actorAssetInfo)
    : EditorWindow("Actor Viewer", editor), actorAssetInfo(actorAssetInfo)
{
    if (actorAssetInfo == nullptr)
        SetOpened(false);
}

void EditorWindowActorViewer::Init()
{
    if (actorAssetInfo == nullptr)
        return;

    actorViewer = editor->GetContext()->GetActorViewer();

    reimportAsset();
}

void EditorWindowActorViewer::Update()
{
}

void EditorWindowActorViewer::Render()
{
    renderViewer();
    renderInspector();
}

void EditorWindowActorViewer::renderViewer()
{
    ImGui::Begin(GetName().c_str());
    
    if (ImGui::Button("Close"))
    {
        SetOpened(false);
    }

    ImGui::Separator();

    viewport->UpdateSize();
    ImGui::Image(actorViewer->GetSceneRenderer()->GetSceneResourceView(),
        viewport->GetSize());

    ImGui::End();
}

void EditorWindowActorViewer::renderInspector()
{
    ImGui::Begin("Actor Inspector");

    if (ImGui::Button("Save"))
    {
        saveAsset();
    }

    ImGui::SameLine();
    if (ImGui::Button("Add Component"))
    {
        
    }

    ImGui::Separator();

    ImGui::Text(actorAssetInfo->GetName().c_str());
    ImGui::Separator();

    ImGui::End();
}

void EditorWindowActorViewer::saveAsset()
{
    editor->GetContext()->GetAssetManager()->SaveAsset(actorAssetInfo->GetAssetNode());

    reimportAsset();
}

void EditorWindowActorViewer::reimportAsset()
{
    
}
